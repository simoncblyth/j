nightly_tests_sql_schema_for_grafana_consumption.rst
=====================================================

overview
----------

* too difficult to come up with general schema from nothing

* instead start with cxs_min.sh sreport and work out
  how to aggregate multiple such reports into sqlite3 db
  that can be grafana queried

* for sqlite3 mechanics see::

    ~/opticks/sysrap/NSQLite.h
    ~/np/NSQLite.h
    ~/np/tests/NSQLite_test.sh



Ideas for opticks monitoring info
-----------------------------------

run level
~~~~~~~~~~

* currently this info mostly contained in run_meta.txt

Strings:

* commandline
* relevant env
* GPU type
* CPU type
* CPU node
* software versions : Opticks,Geant4,CUDA,OptiX,Driver
* geometry name
* geometry digest

seconds:

* start time
* end time

microseconds:

* time to initialize
* geometry upload time

counts:

* num_evt simulated  (typically tests keep this low, up to 20)
* max VRAM (?)

Modes (HMM: in principal could be varied by evt - but so far have not done that)

* hit_mode : lite/full
* merge_mode : cpu/gpu merge



simulated evt level (only ~10 ints per evt would be good)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* TODO: gather the below summary info from ranges array
  (which comes from SProf.txt) and directly from SProf.txt annotations

  * NB this processing must be done from SProf as cannot assume SEvt saving in production

* TODO: review the processing that derives ranges from SProf.txt


Delta Times (differences between epoch microsecond stamps):

* start   : everything before upload
* genstep upload
* simulate kernel
* download
* postprocess (eg CPU merge OR localize) [HMM: MAYBE DONT HAVE THESE YET IN RANGES?]
* total  [ARRANGE FOR THE SUM OF THE ABOVE RANGES TO EQUAL THIS, BY DESIGN]

Counts:

* num_launch [multi-launch will impact times]
* num_photon
* num_genstep
* num_hit

HMM: MAYBE sevrec.h to solidify these ? CAN sevrec.h be populated from sreport/ranges ?


SProf.hh + ranges review
--------------------------



cxs_min.sh ranges which are derived from SProf.txt stamps
-----------------------------------------------------------


* What granularity of entry ?

  * cxs_min.sh running scans across multiple SEvt with different photon counts, with the timing of the first usually being whacky
  * should there be one table row per SEvt ? (excluding the first)  YEP : THATS SIMPLEST FOR ANALYSIS

Full ranges array not needed, just need:


::

    In [1]: f.ranges
    Out[1]:
    array([[1782097507944130, 1782097507951014,             6884,                0,                2],
           [1782097507951014, 1782097509113453,          1162439,                2,                3],
           [1782097509113494, 1782097509501418,           387924,                4,                5],

           [1782097509501775, 1782097509501818,               43,                9,               10],
           [1782097509501825, 1782097509515735,            13910,               11,               12],
           [1782097509515735, 1782097509813007,           297272,               12,               13],
           [1782097509813007, 1782097509831240,            18233,               13,               14],

           [1782097509897984, 1782097509898007,               23,               21,               22],
           [1782097509898014, 1782097509898896,              882,               23,               24],
           [1782097509898896, 1782097510191688,           292792,               24,               25],
           [1782097510191688, 1782097510212450,            20762,               25,               26]])

    In [2]: f.ranges_label

    In [3]: f.ranges_labels
    Out[3]: array(['ta', 'tb', 'ab', 'ia', 'ib'], dtype='<U2')

    In [4]: f.ranges_names
    Out[4]:
    array(['SEvt__Init_RUN_META:CSGFoundry__Load_HEAD:init', 'CSGFoundry__Load_HEAD:CSGFoundry__Load_TAIL:load_geom', 'CSGOptiX__Create_HEAD:CSGOptiX__Create_TAIL:upload_geom',
           'A000_QSim__simulate_HEAD:A000_QSim__simulate_LBEG:slice_genstep', 'A000_QSim__simulate_PRUP:A000_QSim__simulate_PREL:upload genstep slice',
           'A000_QSim__simulate_PREL:A000_QSim__simulate_POST:simulate slice', 'A000_QSim__simulate_POST:A000_QSim__simulate_DOWN:download slice',
           'A001_QSim__simulate_HEAD:A001_QSim__simulate_LBEG:slice_genstep', 'A001_QSim__simulate_PRUP:A001_QSim__simulate_PREL:upload genstep slice',
           'A001_QSim__simulate_PREL:A001_QSim__simulate_POST:simulate slice', 'A001_QSim__simulate_POST:A001_QSim__simulate_DOWN:download slice'], dtype='<U70')

    In [5]: f.ranges_names.reshape(-1,1)
    Out[5]:
    array([['SEvt__Init_RUN_META:CSGFoundry__Load_HEAD:init'],
           ['CSGFoundry__Load_HEAD:CSGFoundry__Load_TAIL:load_geom'],
           ['CSGOptiX__Create_HEAD:CSGOptiX__Create_TAIL:upload_geom'],
           ['A000_QSim__simulate_HEAD:A000_QSim__simulate_LBEG:slice_genstep'],
           ['A000_QSim__simulate_PRUP:A000_QSim__simulate_PREL:upload genstep slice'],
           ['A000_QSim__simulate_PREL:A000_QSim__simulate_POST:simulate slice'],
           ['A000_QSim__simulate_POST:A000_QSim__simulate_DOWN:download slice'],
           ['A001_QSim__simulate_HEAD:A001_QSim__simulate_LBEG:slice_genstep'],
           ['A001_QSim__simulate_PRUP:A001_QSim__simulate_PREL:upload genstep slice'],
           ['A001_QSim__simulate_PREL:A001_QSim__simulate_POST:simulate slice'],
           ['A001_QSim__simulate_POST:A001_QSim__simulate_DOWN:download slice']], dtype='<U70')

    In [6]: f.run
    Out[6]: array([0.], dtype=float32)

    In [7]: f.run_meta
    Out[7]:
    _init_stamp:1782097507944186
    _init_stamp_Fmt:2026-06-22T11:05:07..944






[sreport.desc_ranges ranges : (11, 5, )
.sreport.desc_ranges.descTable  ( ta,tb : range begin,end timestamps expressed as seconds from first timestamp, ab: (tb-ta) )
[NP::descTable_ {} (11, 5, )
                                                  ta                tb                ab                ia                ib          TS_DELTA
                              init          0.000000          0.006884              6884                 0                 2          0.006884                              init
                         load_geom          0.006884          1.169323           1162439                 2                 3          1.162439                         load_geom
                       upload_geom          1.169364          1.557288            387924                 4                 5          0.387924                       upload_geom
                     slice_genstep          1.557645          1.557688                43                 9                10          0.000043                     slice_genstep
              upload genstep slice          1.557695          1.571605             13910                11                12          0.013910              upload genstep slice
                    simulate slice          1.571605          1.868877            297272                12                13          0.297272                    simulate slice
                    download slice          1.868877          1.887110             18233                13                14          0.018233                    download slice
                     slice_genstep          1.953854          1.953877                23                21                22          0.000023                     slice_genstep
              upload genstep slice          1.953884          1.954766               882                23                24          0.000882              upload genstep slice
                    simulate slice          1.954766          2.247558            292792                24                25          0.292792                    simulate slice
                    download slice          2.247558          2.268320             20762                25                26          0.020762                    download slice
num_timestamp 22 auto-offset from t0 1782097507944130
                            TOTAL:          15842132          18043296           2201164               144               156

 0 :                ta : ta
 1 :                tb : tb
 2 :                ab : ab
 3 :                ia : ia
 4 :                ib : ib

                              init : SEvt__Init_RUN_META:CSGFoundry__Load_HEAD:init
                         load_geom : CSGFoundry__Load_HEAD:CSGFoundry__Load_TAIL:load_geom
                       upload_geom : CSGOptiX__Create_HEAD:CSGOptiX__Create_TAIL:upload_geom
                     slice_genstep : A000_QSim__simulate_HEAD:A000_QSim__simulate_LBEG:slice_genstep
              upload genstep slice : A000_QSim__simulate_PRUP:A000_QSim__simulate_PREL:upload genstep slice
                    simulate slice : A000_QSim__simulate_PREL:A000_QSim__simulate_POST:simulate slice
                    download slice : A000_QSim__simulate_POST:A000_QSim__simulate_DOWN:download slice
                     slice_genstep : A001_QSim__simulate_HEAD:A001_QSim__simulate_LBEG:slice_genstep
              upload genstep slice : A001_QSim__simulate_PRUP:A001_QSim__simulate_PREL:upload genstep slice
                    simulate slice : A001_QSim__simulate_PREL:A001_QSim__simulate_POST:simulate slice
                    download slice : A001_QSim__simulate_POST:A001_QSim__simulate_DOWN:download slice
]NP::descTable_ {} (11, 5, )









monitoring schema - up in the air
-----------------------------------


::

    -- 1. Main Job Inventory (Every job gets a row here)
    CREATE TABLE IF NOT EXISTS jobs (
        job_id TEXT PRIMARY KEY,
        job_type TEXT NOT NULL,
        timestamp TEXT NOT NULL,
        cmdline TEXT,
        opticks_version TEXT,
        geometry_digest TEXT,
        total_wall_time_ms REAL,
        pure_sim_time_ms REAL,
        num_photons INTEGER,
        num_hits INTEGER
    );

    -- 2. Job-Specific Meta-Data (Linked via Foreign Key)
    -- Filled ONLY if job_type == 'G4GUN_INJECTION'
    CREATE TABLE IF NOT EXISTS job_perf_g4gun (
        job_id TEXT PRIMARY KEY,
        particle TEXT,
        energy_mev REAL,
        pos_x REAL, pos_y REAL, pos_z REAL,
        FOREIGN KEY(job_id) REFERENCES jobs(job_id) ON DELETE CASCADE
    );



grafana demo data
-------------------

See ~/env/tool/grafana/insert.sh

::

    [blyth@localhost grafana]$ sqlite3 /usr/local/grafana/mock_data/test_metrics.db
    SQLite version 3.34.1 2021-01-20 14:10:07
    Enter ".help" for usage hints.
    sqlite> .schema
    CREATE TABLE device_telemetry (
        t TEXT NOT NULL,
        hostname TEXT NOT NULL,
        cpu_utilization REAL,
        memory_utilization REAL
    );
    sqlite> .mode table
    sqlite> select * from device_telemetry ;
    +---------------------+----------+-----------------+--------------------+
    |          t          | hostname | cpu_utilization | memory_utilization |
    +---------------------+----------+-----------------+--------------------+
    | 2026-06-26 06:10:43 | node-01  | 42.5            | 68.2               |
    | 2026-06-26 06:15:43 | node-01  | 48.1            | 68.4               |
    | 2026-06-26 06:20:43 | node-01  | 55.0            | 71.0               |
    | 2026-06-26 06:25:43 | node-01  | 63.8            | 72.1               |
    | 2026-06-26 06:30:43 | node-01  | 51.2            | 70.5               |
    | 2026-06-26 06:10:43 | node-02  | 12.1            | 34.0               |
    | 2026-06-26 06:15:43 | node-02  | 14.5            | 34.1               |
    | 2026-06-26 06:20:43 | node-02  | 11.2            | 33.9               |
    | 2026-06-26 06:25:43 | node-02  | 18.9            | 35.2               |
    | 2026-06-26 06:30:43 | node-02  | 15.4            | 34.8               |
    +---------------------+----------+-----------------+--------------------+
    sqlite>



grafana consumption  needs to be kept in mind for schema definition
------------------------------------------------------------------------

::

    -- Table tracking overall run metadata
    CREATE TABLE test_runs (
        run_id INTEGER PRIMARY KEY AUTOINCREMENT,
        run_date TEXT NOT NULL,          -- e.g., '2026-06-25'
        start_time TEXT NOT NULL,        -- ISO-8601 string
        end_time TEXT,
        git_branch TEXT NOT NULL,        -- e.g., 'main', 'feature-v2'
        git_commit TEXT NOT NULL,
        status TEXT NOT NULL             -- 'PASSED', 'FAILED'
    );

    -- Table tracking individual test execution times within a run
    CREATE TABLE test_results (
        result_id INTEGER PRIMARY KEY AUTOINCREMENT,
        run_id INTEGER,
        test_name TEXT NOT NULL,         -- e.g., 'test_ray_tracing_bounds'
        duration_seconds REAL,           -- Performance metric
        status TEXT NOT NULL,            -- 'PASS', 'FAIL', 'SKIP'
        FOREIGN KEY(run_id) REFERENCES test_runs(run_id)
    );



grafana "bar chart" query to show how test suite running time changes from night to night::

    SELECT
      run_id AS metric,
      run_date,
      (strftime('%s', end_time) - strftime('%s', start_time)) AS value
    FROM test_runs
    ORDER BY run_id DESC
    LIMIT 30; -- Show the last 30 nightly runs



The most effective pattern for CI/CD data in Grafana is creating a dashboard
that dynamically zooms in on a single specific nightly run.

You can use the Dashboard Variables workflow we just went over, but change the
query to pull your historical test runs::

    Variable Name: $run

    Variable Query: SELECT run_id || ' (' || run_date || ' - ' || git_branch || ')' AS text, run_id AS value FROM test_runs ORDER BY run_id DESC;

Now you can build a panel that dynamically populates with the micro-details of just that selected night's run:


Grafana variable queries : when two columns (text, value) treated as key-value pair

* first column (text) : label in the dropdown
* second column (value) : whats replaced in the parameterized sql queries




