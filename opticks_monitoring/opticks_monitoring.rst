opticks_monitoring_ideas.rst
===============================


Opticks has detailed C++ reporting code that operates ontop of metadata txt and
npy files. I am considering how to standardize this reporting to make it more
useful for long term monitoring as the code and the detector geometry is
changed.


cxs_min.sh creates  a reduced sreport directory, but too much for long term persisting
----------------------------------------------------------------------------------------

Too many files in the sreport folder to realistically persist::

    [lo] A[blyth@localhost ALL1_Debug_Philox_medium_scan_first_sreport]$ find . -type f
    ./NPFold_index.txt
    ./subprofile/NPFold_index.txt
    ./subprofile/a/NPFold_index.txt
    ./subprofile/a/subprofile_names.txt
    ./subprofile/a/NPFold_names.txt
    ./subprofile/a/subprofile_meta.txt
    ./subprofile/a/subprofile_labels.txt
    ...
    ./subcount/a_names.txt
    ./subcount/NPFold_names.txt
    ./subcount/a_labels.txt
    ./subcount/a.npy
    ./runprof_meta.txt
    ./submeta_NumPhotonCollected/NPFold_index.txt
    ./submeta_NumPhotonCollected/b.npy
    ./submeta_NumPhotonCollected/a_names.txt
    ./submeta_NumPhotonCollected/NPFold_names.txt
    ./submeta_NumPhotonCollected/a_labels.txt
    ./submeta_NumPhotonCollected/a.npy
    ./run_meta.txt


What is needed for long term Opticks monitoring:

1. summarization step capturing essentials into a job summary folders containing a few files:

   * <job_id>.json + handful of serialized NPY (.npy .txt) referenced from the json
   * HMM: MANY DIFFERENT TYPES OF JOBS - EG PHOTONS INJECTED IN DIFFERENT PLACES IN DETECTOR

     * json needs to capture the commandlines and environment that configure this

   * Essentially this is just adding a json sidecar top level summary file to the NPFold
   * MOST OF THE WORK IS DESIGNING THE SUMMARY FOLDER CONTENT

2. ingest into sqlite3 step - aggregating metrics for convenient monitoring

   * code to ingest the job summary folders into sqlite3 tables (NPFold.h is C++ so makes sense to use C/C++ API to sqlite3 for this)
   * DB should be recreatable from input folders - for ease of transition to different tech

3. using the sqlite3 database from analysis/monitoring tools

   * probably rather standard





