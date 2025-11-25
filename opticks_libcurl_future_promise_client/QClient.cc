/**


Thinking about how to implement an Opticks client that makes libcurl based
requests to an Opticks server. I think this may have lots of similarity with
implementing progressive launches where while gensteps are collected async CUDA
launches are done that return future objects that are waited on and combined at
the end of the Geant4 event. Does that make sense ? I guess network latency
will be drastically more than local CUDA latency so the parameters of what
photon count in the gensteps is appropriate for making the server request will
be very difficult but other than that much of the machinery of future objects
could be shared?


**/


struct Propagator {
    virtual future_t launch(const Genstep& gs) = 0;
    virtual void     wait(future_t)            = 0;
    virtual NP*      download(future_t)        = 0;
};



class QClient {
    CURLM* multi;
    std::unordered_map<CURL*, std::promise<NP*>> promises;

    future<NP*> propagate(const NP* gs) {
        auto promise = std::make_shared<std::promise<NP*>>();
        auto future  = promise->get_future();

        CURL* eh = curl_easy_init();
        // set URL, headers (Content-Type: application/octet-stream)
        // curl_easy_setopt(eh, CURLOPT_POSTFIELDS, gs->bytes());
        // curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, ...);
        // attach userp = promise.get()

        curl_multi_add_handle(multi, eh);
        promises[eh] = std::move(promise);
        return future;
    }

    void update() {
        int still_running;
        curl_multi_wait(multi, nullptr, 0, 1000, nullptr);
        curl_multi_perform(multi, &still_running);

        CURLMsg* msg;
        int msgs_left;
        while ((msg = curl_multi_info_read(multi, &msgs_left))) {
            if (msg->msg == CURLMSG_DONE) {
                CURL* eh = msg->easy_handle;
                auto prom = promises.extract(eh);
                // parse received buffer into NP array
                prom.value()->set_value(received_array);
                curl_multi_remove_handle(multi, eh);
                curl_easy_cleanup(eh);
            }
        }
    }
};











std::future<NP*> QClient::propagate(const NP* gs)
{
    auto promise = std::make_shared<std::promise<NP*>>();
    auto future  = promise->get_future();

    CURL* eh = curl_easy_init();
    // ... setup POST, headers, etc ...

    // store both promise and buffer we will write into
    struct Request {
        std::shared_ptr<std::promise<NP*>> prom;
        std::vector<char> recv_buffer;
    };
    auto req = std::make_shared<Request>();
    req->prom = promise;

    curl_easy_setopt(eh, CURLOPT_WRITEDATA,     req.get());
    curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
        auto* r = static_cast<Request*>(userdata);
        size_t bytes = size * nmemb;
        r->recv_buffer.insert(r->recv_buffer.end(), ptr, ptr+bytes);
        return bytes;
    });

    curl_multi_add_handle(multi, eh);
    active_requests[eh] = std::move(req);

    return future;
}


