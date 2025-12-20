#!/bin/bash

# Define the hung repository mount point
MNT_POINT="/cvmfs/juno.ihep.ac.cn"

echo "--- Starting CVMFS Recovery for $MNT_POINT ---"

# 1. Kill all processes currently accessing the mount point
echo "[1/4] Killing processes accessing $MNT_POINT..."
sudo fuser -mvk -9 "$MNT_POINT" 2>/dev/null

# 2. Attempt a lazy, forced unmount
# -f: force (useful for unreachable NFS/CVMFS)
# -l: lazy (detaches the filesystem from the tree immediately)
echo "[2/4] Attempting forced lazy unmount..."
sudo umount -fl "$MNT_POINT"

# 3. Kill any remaining orphaned CVMFS processes for this repo
echo "[3/4] Cleaning up orphaned cvmfs2 processes..."
pgrep -f "cvmfs2.*$MNT_POINT" | xargs -r sudo kill -9

# 4. Restart CVMFS services to reload the mount
echo "[4/4] Reloading CVMFS..."
sudo cvmfs_config reload
sudo cvmfs_config probe

echo "--- Recovery Complete ---"
df -h | grep cvmfs


