#!/bin/bash

# Target repository
REPO="juno.ihep.ac.cn"
MOUNT_PT="/cvmfs/$REPO"

echo "Attempting to recover CVMFS mount: $MOUNT_PT"

# 1. Try the official CVMFS tool first (with a timeout)
echo "Step 1: Running cvmfs_config umount..."
sudo timeout 10 cvmfs_config umount $REPO

# 2. Use Lazy Unmount (the most effective way to detach a hung FUSE mount)
if mountpoint -q "$MOUNT_PT" || lsdir "$MOUNT_PT" &>/dev/null; then
    echo "Step 2: Mount point still active. Performing lazy unmount..."
    sudo umount -l "$MOUNT_PT"
fi

# 3. Kill hung CVMFS processes related to this repo
# We use pkill -9 with -f to match the full command line argument
echo "Step 3: Killing hung cvmfs2 processes for $REPO..."
sudo pkill -9 -f "cvmfs2.*$REPO"

# 4. Kill any lingering mount helpers
echo "Step 4: Killing lingering mount.cvmfs processes..."
sudo pkill -9 -f "mount.cvmfs.*$REPO"

# 5. Final Cleanup: Refresh Autofs if you are using it
if systemctl is-active --quiet autofs; then
    echo "Step 5: Restarting autofs to clean up mount table..."
    sudo systemctl restart autofs
fi

echo "Recovery attempt complete. Checking status..."
cvmfs_config probe $REPO
