cvmfs_config.rst
====================


default.conf
    upstream blueprint : NEVER MODIFY THIS FILE


default.local
     Overrides any parameter defined in default.conf
     Applies to all repo mounted on this workstation

::

    1. /etc/cvmfs/default.conf         <- Baseline defaults (System-provided)
    2. /etc/cvmfs/default.d/*.conf     <- Addon features (e.g., grid middleware defaults)
    3. /etc/cvmfs/default.local        <- Your global workstation tweaks
    4. /etc/cvmfs/domain.d/*.conf      <- Settings tied to a domain (e.g., *.ihep.ac.cn)
    5. /etc/cvmfs/config.d/*.conf      <- Settings specific to a single repository 
                                          (e.g., opticks.ihep.ac.cn.conf) 


If you want a setting to affect every mount point (like setting a universal
network timeout or choosing an SSD cache directory), put it in default.local.

If you want a setting to only affect Opticks but leave Juno alone, create a
file named /etc/cvmfs/config.d/opticks.ihep.ac.cn.conf and place the parameters
there.


To verify exactly what parameters CVMFS is currently utilizing after combining
these files, you can run::

    cvmfs_config showconfig juno.ihep.ac.cn


Recover pristine default.conf
-------------------------------

::

    cd /tmp
    dnf clean expire-cache
    dnf download cvmfs-2.13.2-1.el9.x86_64


    # Extract the file into /tmp/etc/cvmfs/default.conf
    rpm2cpio cvmfs-2.13.2-1.el9.x86_64.rpm | cpio -ivd ./etc/cvmfs/default.conf

    # Back up your modified version
    sudo mv /etc/cvmfs/default.conf /etc/cvmfs/default.conf.bak

    # Place the pristine version into the system directory
    sudo cp etc/cvmfs/default.conf /etc/cvmfs/default.conf


    sudo cvmfs_config reload


Gemini : Problem with overlarge cache in CVMFS
--------------------------------------------------

CVMFS doesn't manage its cache like a normal, lightweight database. It treats
the disk cache as a POSIX filesystem structure, and your settings are pushing
it to the absolute limit.

The Cache Manager Overload
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Look at your ps aux output from earlier::

    __cachemgr__ . 11 12 209715200000 104857600000

Your cache manager is tracking up to 210 GB of data. When the cache gets full,
or when CVMFS runs its cleanup routines, the internal __cachemgr__ process has
to scan, lock, and garbage-collect hundreds of thousands of small files.

If your cache directory is on a traditional hard drive, or on an SSD
experiencing high I/O wait from GPU jobs, the kernel FUSE layer will deadlock
waiting for file locks, dropping your processes straight into an un-killable D
state.



The 32 GB RAM Cache Danger (CVMFS_MEMCACHE_SIZE=32768)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

While caching metadata in RAM speeds up compilation, 32 GB is dangerously large
for an isolated FUSE module.

When your workstation runs heavy GPU/Opticks workloads, memory pressure spikes.
If the Linux kernel tries to reclaim memory or swap out pages, a massive 32 GB
CVMFS allocation can freeze the FUSE helper threads. A frozen FUSE thread
instantly causes a D-state hang for any process trying to access /cvmfs.










Downsize the cache following Gemini advice : how to optimize /etc/cvmfs/default.local
---------------------------------------------------------------------------------------


::

    CVMFS_REPOSITORIES='juno.ihep.ac.cn,opticks.ihep.ac.cn'
    CVMFS_HTTP_PROXY=DIRECT

    # --- NETWORK TIMEOUTS (Keep these, they are good) ---
    CVMFS_TIMEOUT=5
    CVMFS_TIMEOUT_DIRECT=5
    CVMFS_MAX_RETRIES=3

    # --- DISK CACHE OPTIMIZATION ---
    # Downsize the disk cache. Opticks and Juno datasets don't need 200GB locally.
    # 40-50 GB is usually more than enough for active software stacks.
    CVMFS_QUOTA_LIMIT=50000

    # --- RAM CACHE DOWNSIZE (Critical for Stability) ---
    # Drop this down. 4GB (4096) or 8GB (8192) is massive for just metadata 
    # and won't risk choking your system memory under heavy GPU loads.
    CVMFS_MEMCACHE_SIZE=4096

    # --- METADATA TUNING ---
    # 5 days (7200) is fine, but if IHEP makes an update, you won't see it for days.
    # A standard aggressive workstation setting is 1 day (1440) or 12 hours (720).
    CVMFS_TTL=1440
    CVMFS_NO_STAT_TTL=3600

    # --- FILE DESCRIPTORS ---
    CVMFS_NFILES=500000



Clearing cache
---------------

::

    sudo systemctl stop autofs
    sudo cvmfs_config umount

    sudo cvmfs_config wipecache

    sudo systemctl start autofs






The Difference Between CVMFS_CACHE_SIZE and CVMFS_QUOTA_LIMIT
-----------------------------------------------------------------

CVMFS has two different ways of looking at disk limits depending on whether it
is running an unmanaged cache or a managed (quota-controlled) cache.

CVMFS_CACHE_SIZE (The Unmanaged Threshold):
   This is a legacy/basic setting. It tells the individual CVMFS mount
   process roughly how much disk space it can use in megabytes before it should
   try to run its own self-contained, basic cleanup.
   It operates on a per-repository basis if not managed centrally.

CVMFS_QUOTA_LIMIT (The Managed Quota):
   This setting activates the CVMFS Cache Manager daemon (the __cachemgr__
   processes you saw in your ps aux output).
   When CVMFS_QUOTA_LIMIT is set, the Cache Manager takes strict, centralized
   control over the cache directory shared across all your repositories (juno and
   opticks). It tracks every single file download in a local SQLite database and
   enforces a strict global hard limit.

Why Having Both in Your Old Config Was Dangerous

When you define both variables, they can conflict if they don't match
perfectly, or they can trigger competing cleanup loops.

More importantly, in older configurations, setting a massive CVMFS_CACHE_SIZE
alongside a managed quota can occasionally confuse the FUSE client into
thinking it has more unmanaged headroom than it actually does. If the local
client tries to dump files without informing the central cache manager thread,
the cache manager loses sync, tries to lock the SQLite database to recount the
files, and freezes the FUSE filesystem into a D-state hang.

The Modern Recommendation

In modern versions of CVMFS (like your 2.13.2), if you want to use a strict
shared quota across multiple repositories (which is highly recommended for
workstations mounting both Juno and Opticks), you should only use
CVMFS_QUOTA_LIMIT.

When CVMFS_QUOTA_LIMIT is set, CVMFS automatically sets up the managed cache
and safely ignores or overrides the loose CVMFS_CACHE_SIZE directive.

If you want to keep your configuration clean and robust, you can completely
safely remove or comment out CVMFS_CACHE_SIZE and let CVMFS_QUOTA_LIMIT do all
the heavy lifting:









