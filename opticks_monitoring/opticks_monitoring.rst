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
   * do not want to handle schema migrations - keep DB transient so can change schema whenever need to
   * straightforward use of C API once JobSummary stabilizes

3. using the sqlite3 database from analysis/monitoring tools

   * probably rather standard


Options for srun.h intermediary [nlohmann/json + NPFold.h composite] 
------------------------------------------------------------------------

* https://github.com/nlohmann/json#examples

* extend sreport to add creation of srun.h
 
  * turn that around - srun.h should be created entirely from loaded sreport.h
  * sreport.h currently rather duplicitous - but srun.h can just summarize whats relevant from sreport.h 
    (not depending on sreport, only NPFold, NP, json)

  * srundb.h (adding sqlite3.h dependency can then load the srun.h and create sqlite3 database) 

* persist srun.h into normal persisted NPFold with json inside the folder
* NPFold.h is recursive [it can contain other NPFold.h and so on]
* should srun.h be recursive too ?

Is json needed ?
~~~~~~~~~~~~~~~~~~

* ~/opticks/notes/NLJSON_review.rs
* add json summary to sreport ? 

  * actually json not adding much - NPFold meta and run meta have everything already ?


Alternative to adding srun.h intermediate layer - go direct from sreport to sreportdb ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* create sreportdb that aggregates reports into sqlite db ? 
* sliming down sreport.h is difficult to do though
* it comes down to the sqlite tables - what level of detail to capture  


Thinking about handling of large numbers of sreport 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* gather the 8 sreport.h members : into one "report" NPFold ?

::

    028     NP*       run ;       // dummy array that exists just to hold metadata
     29     NP*       runprof ;   // "prof" would be a better name now : but awkward to change
     30     NP*       ranges ;    // detailed range timing extracted from SProf.txt
     31 
     32     NPFold*   substamp ;
     33     NPFold*   subprofile ;
     34     NPFold*   submeta ;   // folder of arrays of metadata values extracted from folder metadata - NOW ONLY RELEVANT FOR NON-PROFILE INFO
     35     NPFold*   submeta_NumPhotonCollected ; // RE-USE of submeta machinery with a single column - HMM THIS NEEDS TO BE REPLACED WITH SProf ANNOTATIONS
     36     NPFold*   subcount ;
     37 

    073 inline NPFold* sreport::serialize() const
     74 {
     75     NPFold* smry = new NPFold ;
     76     smry->add("run", run ) ;
     77     smry->add("runprof", runprof ) ;
     78     smry->add("ranges", ranges ) ;
     79     smry->add_subfold("substamp", substamp ) ;
     80     smry->add_subfold("subprofile", subprofile ) ;
     81     smry->add_subfold("submeta", submeta ) ;
     82     smry->add_subfold("submeta_NumPhotonCollected", submeta_NumPhotonCollected ) ;
     83     smry->add_subfold("subcount", subcount ) ;
     84     return smry ;
     85 }

     97 inline void sreport::save(const char* dir) const
     98 {
     99     NPFold* smry = serialize();
    100     smry->save_verbose(dir);
    101 }


Actually no point persisting saves all into one folder anyhow::


    [lo] A[blyth@localhost np]$ cd /data1/blyth/tmp/GEOM/J26_1_1_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_medium_scan_first_sreport
    [lo] A[blyth@localhost ALL1_Debug_Philox_medium_scan_first_sreport]$ l
    total 68
    0 -rw-r--r--. 1 blyth blyth    0 Jun 25 11:31 NPFold_names.txt
    4 -rw-r--r--. 1 blyth blyth   95 Jun 25 11:31 NPFold_index.txt
    4 -rw-r--r--. 1 blyth blyth   15 Jun 25 11:31 ranges_labels.txt
    4 -rw-r--r--. 1 blyth blyth  687 Jun 25 11:31 ranges_names.txt
    4 -rw-r--r--. 1 blyth blyth  568 Jun 25 11:31 ranges.npy
    4 -rw-r--r--. 1 blyth blyth  132 Jun 25 11:31 run.npy
    4 -rw-r--r--. 1 blyth blyth   21 Jun 25 11:31 runprof_labels.txt
    4 -rw-r--r--. 1 blyth blyth 2329 Jun 25 11:31 runprof_meta.txt
    4 -rw-r--r--. 1 blyth blyth   80 Jun 25 11:31 runprof_names.txt
    4 -rw-r--r--. 1 blyth blyth  224 Jun 25 11:31 runprof.npy
    4 -rw-r--r--. 1 blyth blyth 2116 Jun 25 11:31 run_meta.txt
    4 drwxr-xr-x. 7 blyth blyth 4096 Jun 18 17:31 .
    4 drwxr-xr-x. 2 blyth blyth 4096 Jun 18 17:31 subcount
    4 drwxr-xr-x. 2 blyth blyth 4096 Jun 18 17:31 submeta
    4 drwxr-xr-x. 2 blyth blyth 4096 Jun 18 17:31 submeta_NumPhotonCollected
    4 drwxr-xr-x. 8 blyth blyth 4096 Jun 18 17:31 ..
    4 drwxr-xr-x. 3 blyth blyth 4096 Jun 18 17:31 subprofile
    4 drwxr-xr-x. 3 blyth blyth 4096 Jun 18 17:31 substamp
    [lo] A[blyth@localhost ALL1_Debug_Philox_medium_scan_first_sreport]$ 


Collecting sreport can be achieved by adopting a naming convention with incrementing zero padded 
report index for the folder name "sreport_0000000"

* see ~/o/sysrap/tests/sfilesystem_test.sh

 

Grafana
----------

* https://andidog.de/blog/2022-04-21-grafana-dashboards-best-practices-dashboards-as-code


Grafana Sqlite
------------------

* https://grafana.com/grafana/plugins/frser-sqlite-datasource/

::

    grafana-cli plugins install frser-sqlite-datasource


I want to use Grafana or similar to present software metrics persisted into
sqlite3 database ? How to do that ? What sort of tables do I need to prepare to
set this up ?



General query
--------------

I am looking for tools to assist with monitoring of Opticks simulation
performance, monitoring things such as geometry upload, kernel execution time
for different optical photon counts and photon source positions. Its also
important to allow metric presentation thats aware of GPU types used and
software versions.  Opticks currently has custom reporting in C++ that analyses
persisted profile metadata and saved Opticks events - summarizing these into
NPFold.h  folders of NP.hh NumPy format persisted arrays.  What potential tools
should I investigate to setup a monitoring pipeline ? 


The kind of data I want to monitor is coming from nightly gitlab-ci runs over a
suite of simulation integration test runs that will perhaps grow to 20 types of
tests with order 10 things to monitor for each run. So the scale is small
enough for sqlite.  My concern is over flexibility of querying and
presentation. 

Does Grafana give full flexibility of data access eg for comparing metrics
between different GPUs ?



grafana query
--------------

::

    SELECT
        run_date AS time,
        kernel_execution_time AS value,
        gpu_type AS metric  -- Grafana uses this text column to split lines
    FROM opticks_nightly_metrics
    WHERE test_name = '$test_name' -- References the dropdown variable
      AND gpu_type IN ($gpu_types)  -- Multi-select array from dropdown
    ORDER BY run_date ASC;


The test_name is doing lots of work here, could that be a primary key from a test table ?

::

    -- 1. The Registry Table
    CREATE TABLE tests (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        test_name TEXT NOT NULL UNIQUE,          -- e.g., "juno_full_optical"
        geometry_type TEXT,                      -- e.g., "vcf", "gdml"
        description TEXT                         -- e.g., "Full JUNO simulation tracking 1M photons"
    );

    -- 2. The Metrics Ledger Table
    CREATE TABLE test_runs (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        test_id INTEGER NOT NULL,                -- Foreign Key referencing tests.id
        run_date TEXT NOT NULL,                  -- e.g., "2026-06-26 02:00:00"
        git_commit TEXT NOT NULL,
        opticks_version TEXT NOT NULL,
        gpu_type TEXT NOT NULL,                  -- e.g., "RTX_4090"
        metrics TEXT,                            -- The flexible JSON payload (photon counts, kernel times, positions)
        FOREIGN KEY (test_id) REFERENCES tests(id)
    );


    SELECT 
        t.geometry_type,
        AVG(CAST(json_extract(tr.metrics, '$.upload_geometry_time') AS REAL)) AS avg_upload_time
    FROM test_runs tr
    JOIN tests t ON tr.test_id = t.id
    WHERE tr.gpu_type = 'NVIDIA_Blackwell'
    GROUP BY t.geometry_type;





sqlite json_extract
-------------------

::

    -- Example query extracting nested photon source positions and kernel times
    SELECT 
        gpu_type,
        opticks_version,
        CAST(json_extract(metrics, '$.photon_counts.total') AS INT) AS total_photons,
        CAST(json_extract(metrics, '$.kernels.raytrace_time') AS REAL) AS raytrace_time
    FROM simulation_runs
    WHERE gpu_type LIKE '%RTX%'
      AND json_extract(metrics, '$.source_position.z') = 0.0;




OK. I can see its use for time series data.  But how can this work for nightly
test suite runs which yield a bunch of data across a few hours of running tests
each night ?





