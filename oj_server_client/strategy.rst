oj_server_client/strategy : discuss with Gemini
=================================================


Opticks server/client problem description
-------------------------------------------

The application in mind is an Opticks server with libcurl based clients sending
serialized NumPy array gensteps and getting array hits in response. The problem
is very wide range of numbers of photons being generated from the genstep
parameters.  So some requests will be very fast and some would take seconds.


Cost based Throttling / Dual-Lane Queues / Async libcurl client / FastAPI cost control
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is a classic "Heterogeneous Workload" problem in high-performance
computing. In **Opticks**, where a single genstep could represent 10 photons
(instant) or 100 million photons (seconds), treating all POST requests as equal
will lead to **Head-of-Line Blocking**: a tiny, fast request gets stuck behind
a massive one that has saturated the GPU's ray-tracing cores.

To support multiple clients without killing the server, you should implement a
**Cost-Aware Admission Control** system.

### 1. Cost-Based Throttling (The "Photon Credit" System)
Instead of limiting the *number* of requests, limit the *work* being sent to the GPU.

*   **The Logic:** Before accepting the NumPy array, FastAPI should inspect the genstep parameters (specifically the `num_photons` or equivalent sum). 
*   **The Rule:** Your server has a "Compute Budget" of $X$ million photons in flight. 
*   **Implementation:**
    *   If a request asks for 1M photons and you have 50M available in the budget, it passes.
    *   If a request asks for 80M photons but your limit is 50M, return a `429 Too Many Requests` or put it in a "Heavy" queue.

---

### 2. Dual-Lane Virtual Queues (Priority Lane)
To prevent small simulations from being "killed" by large ones, use two different semaphores or queues.
*   **Fast Lane (Small Gensteps):** Reserve a portion of your GPU capacity (e.g., 20%) for gensteps under a certain photon threshold (e.g., < 100k photons). This ensures that interactive clients or small tests always feel responsive.
*   **Batch Lane (Large Gensteps):** Large requests must wait for a specific "Heavy Worker" slot.

---

### 3. Asynchronous libcurl Strategy
On the **client-side**, since some requests take seconds, a standard synchronous `curl_easy_perform` will hang your client UI or thread.
*   **Use `curl_multi`:** This allows your client to send multiple gensteps and "poll" for which ones are finished.
*   **Progress Monitoring:** Since you are using NumPy, you can use libcurl's
`XFERINFOFUNCTION` to track the download of the "Hits" array. If the server is
throttled, the client will see the data transfer rate drop, providing a natural
way to show a progress bar.

---

### 4. Memory-Gating (VRAM Safety)
Opticks is very efficient, but massive photon counts require large buffers for "Hits" (the response arrays). 
*   **Server Check:** Calculate the expected size of the response NumPy array:
    $$ \text{Expected Size} = \text{Num\_Photons} \times \text{Size\_of\_Hit\_Struct} $$
*   **Pre-emptive Rejection:** If the expected response size exceeds available VRAM or a safe system RAM buffer, reject the POST *before* the GPU starts work. This prevents the server from crashing mid-simulation.

---

### 5. Implementation in FastAPI
Since you are using FastAPI, you can use a **Middleware** or a **Dependency**
to calculate the "cost" of the incoming NumPy array.

```python
from fastapi import FastAPI, HTTPException, Request
import numpy as np
import asyncio

# The "Global GPU Budget" in millions of photons
MAX_PHOTONS_IN_FLIGHT = 100 
current_photons = 0
lock = asyncio.Lock()

@app.post("/simulate")
async def simulate(genstep_data: bytes):
    global current_photons
    
    # 1. Quick decode of genstep to see photon count
    # (Assuming gensteps have a fixed structure where count is at a specific offset)
    gensteps = np.frombuffer(genstep_data, dtype=np.float32).reshape(-1, 6)
    requested_photons = int(np.sum(gensteps[:, 0])) # Example index for count

    # 2. Admission Control
    if requested_photons > MAX_PHOTONS_IN_FLIGHT:
        raise HTTPException(status_code=413, detail="Genstep too large for this server")

    # 3. Wait for space in the "budget"
    while True:
        async with lock:
            if current_photons + requested_photons <= MAX_PHOTONS_IN_FLIGHT:
                current_photons += requested_photons
                break
        await asyncio.sleep(0.1) # Back off and wait

    try:
        # 4. Perform the actual Opticks/OptiX work
        hits = await run_opticks_gpu(gensteps)
        return hits.tobytes()
    finally:
        # 5. Release budget
        async with lock:
            current_photons -= requested_photons
```

### Summary of the "Best" Configuration:
1.  **Client:** Use `libcurl` multi-interface to handle the variability without blocking.
2.  **Server API:** Use **FastAPI Semaphores** based on *photon count*, not *request count*.
3.  **GPU:** Use **NVIDIA MPS** to allow the "Fast Lane" (small requests) to execute even while a "Heavy Lane" (large request) is occupying the GPU.
4.  **Network:** Set `CURLOPT_TIMEOUT` on the client to a generous value (e.g., 30s) but implement a shorter `CURLOPT_CONNECTTIMEOUT` to detect server death quickly.




How does libcurl client handle : HTTP 429 - too many requests
-----------------------------------------------------------------

What happens at libcurl client end when server responds with : too many
requests ? Can it be made to try again later ? How is that configured ? 


Client handling 429 / Client libcurl Retry loop
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


When your **libcurl** client receives an **HTTP 429 Too Many Requests**
response, the library's default behavior is to treat it as a successful
*transfer* (it received a valid HTTP response), even though the *application
logic* failed.

Unlike a network timeout or a DNS error, libcurl **does not automatically retry
a 429 error** unless you explicitly configure it to do so.

---

### 1. What happens at the Client End?
By default, `curl_easy_perform` will return `CURLE_OK` because it successfully communicated with the server. It is up to your code to:
1.  Check the HTTP response code using `curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &code)`.
2.  Identify that the code is **429**.
3.  Read the **Retry-After** header to know how long to wait.

---

### 2. Can it be made to try again automatically?
If you are using the **curl command-line tool**, you can simply use `--retry 5
--retry-all-errors`. However, in **libcurl (the C library)**, there is no
single "RetryOn429" toggle. You have to implement the retry loop yourself.

Fortunately, libcurl provides a helper to parse the server's wait-time for you.

#### The "Retry-After" Helper: `CURLINFO_RETRY_AFTER`
Since version 7.66.0, libcurl can automatically parse the `Retry-After` header
(which can be a number of seconds or a specific date/time) and convert it into
a simple integer for you.

---

### 3. How to configure a Retry Loop
The most robust way to handle this in your Opticks server/client setup is to
wrap your perform call in a logic loop that respects the server's back-off
request.

**Example Logic (C++):**
```cpp
long response_code = 0;
int retries = 3;
curl_off_t retry_wait = 0;

while (retries > 0) {
    res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

        if (response_code == 429) {
            // Ask libcurl how long the server wants us to wait
            curl_easy_getinfo(curl, CURLINFO_RETRY_AFTER, &retry_wait);
            
            if (retry_wait <= 0) retry_wait = 2; // Default fallback (seconds)
            
            fprintf(stderr, "Throttled! Waiting %ld seconds...\n", (long)retry_wait);
            sleep(retry_wait); 
            retries--;
            continue; // Try the POST again
        }
    }
    break; // Exit if success (200 OK) or a non-retryable error
}
```

---

### 4. Why this is critical for your GPU Server
In your specific case with **Opticks gensteps**, a 429 response is actually a
"good" thing—it means your server is successfully protecting its VRAM from
crashing. 

* **The Problem:** If you don't handle 429s, your client will simply drop the "Hits" for that genstep, leading to holes in your simulation data.
* **The Fix:** By configuring libcurl to wait and retry, you turn a
**server-side "No"** into a **client-side "Not yet."** The client will pause,
and as soon as the previous heavy GPU simulation finishes, the next request
will go through.

### Summary of Configuration
| Component | Configuration Key | Role |
| :--- | :--- | :--- |
| **Detection** | `CURLINFO_RESPONSE_CODE` | Identifies the **429** error. |
| **Parsing** | `CURLINFO_RETRY_AFTER` | Extracts the wait time from the server header. |
| **Strategy** | **Exponential Backoff** | If the server doesn't provide a `Retry-After`, wait 1s, then 2s, then 4s. |
| **CLI Tool** | `--retry` | The equivalent flag if you were testing via terminal. |

Does your current server send the `Retry-After` header in its FastAPI response, or should we look at how to add that to your "too many photons" logic?





Yes. How to get FastAPI to respond with 429 and a Retry-After ?
----------------------------------------------------------------


To trigger a **429 Too Many Requests** with the appropriate headers in FastAPI,
you shouldn't just "return" a dictionary. You need to raise an `HTTPException`
and manually include the `Retry-After` header in the `headers` argument.

The `Retry-After` header is a standard HTTP field that tells the client (in
your case, the `libcurl` requester) exactly how many seconds to wait before
attempting the POST again.

---

### 1. The Implementation
Here is how you would integrate this into your photon-count "budget" logic.

```python
from fastapi import FastAPI, HTTPException, status
import time

app = FastAPI()

# Example state: 
# In a real app, track this via a global variable or Redis
CURRENT_GPU_LOAD = 95  # Assume 0-100 scale

@app.post("/simulate")
async def run_simulation():
    global CURRENT_GPU_LOAD
    
    # Check if the GPU is "Full"
    if CURRENT_GPU_LOAD > 90:
        # Define how long the client should wait (e.g., 5 seconds)
        wait_time = "5" 
        
        raise HTTPException(
            status_code=status.HTTP_429_TOO_MANY_REQUESTS,
            detail="GPU Compute Budget Exhausted. Please try again later.",
            headers={"Retry-After": wait_time}
        )
    
    # ... perform Opticks work ...
    return {"status": "success"}
```

---

### 2. Why "Retry-After" is Critical for libcurl
By including this header, you turn a "dumb" retry loop into an "intelligent" one. 

1.  **Server Control:** If your GPU simulation is huge and will take 30
seconds, you can set `Retry-After: 30`. The `libcurl` client (using
`CURLINFO_RETRY_AFTER`) will sleep for exactly 30 seconds rather than
"hammering" your server every 1 second and wasting CPU cycles on both ends.

2.  **Standardization:** This is the standard way load balancers and CDNs
handle traffic. If you ever move your Opticks server behind **Nginx** or
**Cloudflare**, your client code won't need to change—it will already know how
to respect those limits.



---

### 3. Dynamic Wait Times
Instead of a hard-coded `5`, you can calculate the wait time based on the
"size" of the photons currently being processed.

```python
# Calculate wait time based on average photon processing speed
# (Estimated Photons Remaining / Photons Per Second)
seconds_to_free_vram = round(remaining_photons / throughput)

raise HTTPException(
    status_code=429,
    detail="Heavy Simulation in Progress",
    headers={"Retry-After": str(max(1, seconds_to_free_vram))}
)
```

### 4. Verifying with `curl`
You can verify your server is sending the header correctly by running this in your terminal:
```bash
curl -I -X POST http://localhost:8000/simulate
```
You should see:
`HTTP/1.1 429 Too Many Requests`
`retry-after: 5`

---

### Pro-Tip: Middleware vs. Endpoint
If you have many different endpoints that all use the GPU, don't repeat this
code in every function. Use a **FastAPI Dependency**.

```python
async def check_gpu_limit():
    if gpu_is_busy():
        raise HTTPException(status_code=429, headers={"Retry-After": "10"})

@app.post("/simulate", dependencies=[Depends(check_gpu_limit)])
async def run_sim():
    ...
```

This keeps your simulation logic clean and ensures that the "throttling gate"
is checked before any heavy NumPy serialization/deserialization even begins. 

Do you currently have a way to track the "active" photon count, or do you need
a suggestion for a thread-safe way to monitor that across multiple FastAPI
workers?





