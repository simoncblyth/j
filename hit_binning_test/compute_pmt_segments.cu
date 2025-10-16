/**


d_offsets (size num_pmts+1) 
    gives start/end indices for each PMT

d_counts 
    gives hit counts per PMT.

**/


void compute_pmt_segments(
    const thrust::device_vector<unsigned>& d_pmt_ids,
    unsigned num_hits,
    unsigned num_pmts,
    thrust::device_vector<unsigned>& d_offsets,
    thrust::device_vector<unsigned>& d_counts
) {
    d_offsets.resize(num_pmts + 1);
    d_counts.resize(num_pmts);

    // Count hits per pmt_id
    thrust::reduce_by_key(
        d_pmt_ids.begin(),
        d_pmt_ids.end(),
        thrust::constant_iterator<unsigned>(1),
        thrust::discard_iterator(),
        d_counts.begin()
    );

    // Compute offsets (exclusive scan)
    thrust::exclusive_scan(d_counts.begin(), d_counts.end(), d_offsets.begin());
    d_offsets[num_pmts] = num_hits;  // End marker
}

