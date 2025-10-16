
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/copy.h>

// Host function to sort hits
void sort_hits_by_pmt_id(Hit* d_hits, unsigned num_hits) {
    // Assume Hit struct
    struct Hit {
        float3 global_pos;
        unsigned pmt_id;
        unsigned transform_idx;
    };

    // Create temporary device vector for pmt_ids
    thrust::device_vector<unsigned> d_pmt_ids(num_hits);
    thrust::device_vector<unsigned> d_indices(num_hits);

    // Extract pmt_ids and initialize indices (0, 1, ..., num_hits-1)
    thrust::copy(
        thrust::make_transform_iterator(d_hits, [](const Hit& h) { return h.pmt_id; }),
        thrust::make_transform_iterator(d_hits + num_hits, [](const Hit& h) { return h.pmt_id; }),
        d_pmt_ids.begin()
    );
    thrust::sequence(d_indices.begin(), d_indices.end());

    // Sort by pmt_id, carrying indices
    thrust::sort_by_key(d_pmt_ids.begin(), d_pmt_ids.end(), d_indices.begin());

    // Reorder hits into new buffer (optional, if needed)
    thrust::device_vector<Hit> d_hits_sorted(num_hits);
    thrust::copy(
        thrust::make_permutation_iterator(d_hits, d_indices.begin()),
        thrust::make_permutation_iterator(d_hits, d_indices.end()),
        d_hits_sorted.begin()
    );

    // Copy back or keep d_indices for kernel
    CUDA_CHECK(cudaMemcpy(d_hits, thrust::raw_pointer_cast(d_hits_sorted.data()), num_hits * sizeof(Hit), cudaMemcpyDeviceToDevice));
}


