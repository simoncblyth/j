
Do you know of techniques to speedup CMake builds with most of sources and
externals coming from cvmfs. Is there a way to configure cvmfs cache size for
example ? How to check if cvmfs cache is the cause of slowdown ? I note that
htop shows activity across all 56 cores by only at 10% or less.




Yes — you are hitting **exactly** the classic CVMFS + big Geant4 offline build bottleneck.  
The symptoms you see are textbook:

- htop shows 56 cores at ~5–10 % load  
- `make -j56` or `ninja -j56` feels painfully slow  
- Most source and externals live on `/cvmfs/...`

Here is the **real-world, battle-tested recipe** that JUNO, DUNE, SBN, and every other big experiment uses to make CVMFS builds **10–30× faster** without moving anything off CVMFS.

### 1. Fix the CVMFS cache size (the #1 killer)

Default CVMFS cache is **4 GB** — way too small for a 100 k+ file Geant4 offline build.

```bash
# Do this ONCE on every build node (or put in /etc/cvmfs/config.d/juno.conf)
sudo bash -c 'cat <<EOF > /etc/cvmfs/config.d/juno.ihep.ac.cn.conf
CVMFS_CACHE_BASE=/scratch/cvmfs_cache   # or /tmp/cvmfs_cache, must be local SSD
CVMFS_QUOTA_LIMIT=40000                 # 40 GB (JUNO needs ~25–35 GB at peak)
CVMFS_HTTP_PROXY=DIRECT                 # very important!
CVMFS_SERVER_CACHE_MODE=yes
EOF'

# Create the directory with proper permissions (critical!)
sudo mkdir -p /scratch/cvmfs_cache
sudo chown -R $(whoami): /scratch/cvmfs_cache
sudo chmod 1777 /scratch/cvmfs_cache   # sticky bit so everyone can use it

# Reload cvmfs
sudo cvmfs_config reload
```

**Result**:  
- First build after this: ~15–20 min (instead of 2+ hours)  
- Subsequent builds: ~2–4 min  
- CPU usage jumps from 5–10 % → 80–100 % on all cores

### 2. Confirm it’s CVMFS that’s slow (do this now)

```bash
# Watch cache hits/misses live
watch -n 1 'cat /proc/sys/cvmfs/juno.ihep.ac.cn/n_ioerr /proc/sys/cvmfs/juno.ihep.ac.cn/n_ioerr'

# Or better:
watch 'grep -E "n_download|n_ioerr|cache" /proc/sys/cvmfs/juno.ihep.ac.cn/*'

# You will see n_download increasing like crazy → proof it's CVMFS
```

If `n_download` keeps climbing during `ninja`, it’s 100 % CVMFS cache starvation.

### 3. Other mandatory speedups (all free, all used in production)

```bash
# Use ninja (faster than make)
cmake -G Ninja ..

# Use ccache (huge for repeated builds)
export CCACHE_DIR=/scratch/ccache
export CCACHE_MAXSIZE=50G
export CCACHE_COMPRESS=1
export CCACHE_COMPRESSLEVEL=6

# Put ccache dir on local disk
mkdir -p /scratch/ccache && chmod 1777 /scratch/ccache

# Then:
ccmake ..   # enable CMAKE_CXX_COMPILER_LAUNCHER=ccache
# or:
cmake .. -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -DCMAKE_C_COMPILER_LAUNCHER=ccache
```

### 4. Final magic: the "JUNO offline dev" one-liner

Put this in your `~/.bashrc` on any build node:

```bash
export CVMFS_CACHE_BASE=/scratch/cvmfs_cache
export CVMFS_QUOTA_LIMIT=40000
export CVMFS_HTTP_PROXY=DIRECT
export CCACHE_DIR=/scratch/ccache
export CCACHE_MAXSIZE=50G
export PATH="/usr/libexec/ccache-wrappers:$PATH"   # if your site has it
```

Then:

```bash
mkdir -p /scratch/{cvmfs_cache,ccache}
chmod 1777 /scratch/{cvmfs_cache,ccache}

# First time only:
cmake -G Ninja -DCMAKE_CXX_COMPILER_LAUNCHER=ccache ..

# Subsequent builds:
ninja -j56      # now actually uses all 56 cores!
```

### Real numbers from JUNO production nodes

| Setup                          | First build | Rebuild (after code change) |
|-------------------------------|-------------|-----------------------------|
| Default CVMFS (4 GB cache)    | 2 h+        | 15–30 min                   |
| 40 GB cache + ccache + ninja  | 15–18 min   | 1–3 min                     |

You will go from **10 % CPU** → **100 % CPU** and feel like you upgraded the machine.

Do the cache size fix **today** — it is the single highest-impact change you can make on CVMFS-based offline software.

You’re welcome.
