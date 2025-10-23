

import numpy as np
from collections import Counter
import hashlib

def hash_array(arr):
    # Convert (4,4) subarray to bytes and compute MD5 hash
    return hashlib.md5(arr.tobytes()).hexdigest()

# Compute hashes for all subarrays
hashes = np.array([hash_array(f.hit[i]) for i in range(f.hit.shape[0])])

# Count occurrences of each hash
hash_counts = Counter(hashes)

# Identify duplicates (hashes with count > 1)
duplicate_hashes = {h for h, count in hash_counts.items() if count > 1}

# Optionally, retrieve the actual subarrays (if needed)
duplicate_indices = [i for i, h in enumerate(hashes) if h in duplicate_hashes]
duplicate_subarrays = f.hit[duplicate_indices]

print(f"Number of duplicated subarrays: {len(duplicate_hashes)}")
for h in duplicate_hashes:
    count = hash_counts[h]
    print(f"Subarray (hash {h}) appears {count} times")
    # Optionally print one example of the subarray
    example_idx = next(i for i, x in enumerate(hashes) if x == h)
    print(f"Example subarray:\n{f.hit[example_idx]}")

