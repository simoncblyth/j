cvmfs/recipe_to_change_cvmfs_cache_size.rst
=============================================



That is a very insightful observation, and you are absolutely correct! **Configuration changes to the CVMFS cache size often require a manual cleanup and restart to take effect cleanly.**

### 🔎 Analysis: Cache Size and Hangs

The problem was indeed likely rooted in your configuration change for the cache, which triggered the initial hang (Cause #1 from our previous analysis).

#### The Role of `CVMFS_QUOTA_LIMIT`

When you increase the `CVMFS_QUOTA_LIMIT` (the maximum allowed size for the cache), the CVMFS client needs to:

1.  **Stop using the old cache size:** The running `cvmfs2` process holds the old size limit in memory.
2.  **Adjust the local cache structure:** The core shared cache database (`cachedb`) needs to be checked against the new, larger quota.
3.  **Handle the lock:** If the `cvmfs2` process is still running with a lock on the old cache state, it will often hang when trying to restart or re-evaluate the size parameters.

If you change the cache size **while the CVMFS client is running or without properly clearing the old cache lock and database**, the client often enters a state of confusion or lockup, resulting in the **Uninterruptible Sleep (`D` state)** we observed. 

### ✅ Action to Prevent Recurrence: Cache Cleanup Procedure

To safely change the CVMFS cache size (`CVMFS_QUOTA_LIMIT`) in the future, follow this procedure to ensure a clean transition:

| Step | Command/Action | Purpose |
| :--- | :--- | :--- |
| **1. Stop Autofs** | `sudo systemctl stop autofs` | Ensures the running `cvmfs2` processes release the cache lock. |
| **2. Verify Processes** | `ps aux | grep cvmfs2` | Crucial: Manually check and kill any remaining hung processes (`sudo kill -9 <PID>`). |
| **3. Clear Cache State** | `sudo rm -f /var/lib/cvmfs/shared/cachedb` | Clears the central database file that tracks the cache structure and size, forcing a complete rebuild on startup. |
| **4. Check/Change Config** | Edit the relevant config file (e.g., `/etc/cvmfs/default.local`) and set the new `CVMFS_QUOTA_LIMIT`. | Ensures the new limit is written before the next startup. |
| **5. Start Autofs** | `sudo systemctl start autofs` | Forces the CVMFS client to start cleanly, read the new limit, and rebuild the cache database. |

Because the cache size change is a fundamental change to the CVMFS runtime environment, it requires this explicit stop-and-clear procedure. Your observation confirms that the combination of this cache change and the incorrect hostname was the perfect storm that created the persistent hang.


