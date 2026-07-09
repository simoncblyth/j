opticks_monitoring_schema
==========================


Overview
----------

* try out schema and ingestion from NP array to DB in ~/np/tests/NSQLite_test.sh
* first cut of evsmry loading is working
* DONE: run metadata and initialization timings loading

* see ~/o/sysrap/sreportdb.sql



While schema in development regard the reports as the persisted output
and the db as a transient cherry on top - so can keep rebuilding the db
from the archive of reports.

* https://code.ihep.ac.cn/blyth/oj/-/pipeline_schedules


DONE
-----

1. DONE : configure cxs_min running - as early gitlab-ci stage
2. DONE : arrange for reports to be archived to non /tmp folders using sreport::save_into_archive

   * just need to set SREPORT_ARCHIVE_DIR to directory owned by gitlab-runner

3. DONE : add last gitlab-ci stage that uses sreportdb.sh to ingests from SREPORT_ARCHIVE_DIR creating sqlite3 database

   * HMM: the db needs to be at a path that grafana is configured to read from

::

    export SREPORT_ARCHIVE_DIR=/data1/gitlab-runner/sreport_archive



Gemini discussion
-------------------


For long term persisisting for Opticks monitoring I am developing a summary 2d NP array with the below columns::

   std::vector<std::string> labels = {
         "index",
         "timestamp",
         "genstep",
         "photon",
         "hit",
         "launch",
         "dt_upload",
         "dt_simulate",
         "dt_download" };

For monitoring, I plan to import the arrays derived from nightly test runs into
an sqlite3 database for Grafana presentation. What schema do you suggest ? All
the quantities are integers. The timestamp definitely needs int64_t other
fields could use int32_t.


::

    CREATE TABLE opticks_monitoring (
        -- Primary identification for each nightly run record
        id INTEGER PRIMARY KEY AUTOINCREMENT,

        -- Core Identifiers & Times
        event_index   INTEGER NOT NULL, -- The "index" column from your array
        timestamp     INTEGER NOT NULL, -- Unix epoch (microseconds or milliseconds)

        -- Absolute Counts / Workload
        genstep_count INTEGER NOT NULL,
        photon_count  INTEGER NOT NULL,
        hit_count     INTEGER NOT NULL,

        -- Duration Metrics (stored as integers, e.g., microseconds)
        dt_launch     INTEGER NOT NULL, -- The "launch" column
        dt_upload     INTEGER NOT NULL,
        dt_simulate   INTEGER NOT NULL,
        dt_download   INTEGER NOT NULL
    ) STRICT;

    -- Critical index for Grafana time-series performance
    CREATE INDEX idx_opticks_time ON opticks_monitoring(timestamp);



Grafana querying::

    SELECT
      timestamp / 1000000 AS time, -- Convert microseconds to seconds for Grafana
      dt_simulate AS "Simulation Time",
      dt_upload AS "Upload Time",
      dt_download AS "Download Time"
    FROM opticks_monitoring
    WHERE timestamp >= $__unixEpochFrom()*1000000 AND timestamp <= $__unixEpochTo()*1000000
    ORDER BY timestamp ASC;




Each opticks run also has a bunch of mostly text metadata like software
versions, commandline, type of GPU, geometry name, geometry digest etc.., and a
few initialization timings like geometry upload time, and number of events
simulated.  How do you suggest to capture the connection between the monitoring
run table and event table ?


::

      ┌─────────────────────────────────┐
      │              RUNS               │  (One row per nightly test run)
      ├─────────────────────────────────┤
      │  id (PRIMARY KEY)               │◄──────┐
      │  gpu_type, software_version...  │       │
      └─────────────────────────────────┘       │
                                                │ Connected via
                                                │ Foreign Key
      ┌─────────────────────────────────┐       │
      │             EVENTS              │       │
      ├─────────────────────────────────┤       │
      │  id (PRIMARY KEY)               │       │
      │  run_id (FOREIGN KEY) ──────────┼───────┘
      │  event_index, dt_simulate...    │  (Multiple rows pointing to the same run)
      └─────────────────────────────────┘



::

    -- 1. THE PARENT TABLE: Core Run Metadata
    CREATE TABLE opticks_runs (
        id                  INTEGER PRIMARY KEY AUTOINCREMENT,
        run_timestamp       INTEGER NOT NULL, -- When the run started

        -- Software & Hardware Environment (Text Metadata)
        software_version    TEXT NOT NULL,
        command_line        TEXT NOT NULL,
        gpu_type            TEXT NOT NULL,
        geometry_name       TEXT NOT NULL,
        geometry_digest     TEXT NOT NULL,

        -- Global Run Metrics / Initialization Timings
        dt_geometry_upload  INTEGER NOT NULL, -- Init timing
        total_events        INTEGER NOT NULL  -- Target total count expected
    ) STRICT;


    -- 2. THE CHILD TABLE: Granular Per-Event Metrics
    CREATE TABLE opticks_events (
        id            INTEGER PRIMARY KEY AUTOINCREMENT,

        -- The connection link to the parent run
        run_id        INTEGER NOT NULL,

        -- Your existing array data
        event_index   INTEGER NOT NULL,
        genstep_count INTEGER NOT NULL,
        photon_count  INTEGER NOT NULL,
        hit_count     INTEGER NOT NULL,
        dt_launch     INTEGER NOT NULL,
        dt_upload     INTEGER NOT NULL,
        dt_simulate   INTEGER NOT NULL,
        dt_download   INTEGER NOT NULL,

        -- Enforce the relational integrity
        FOREIGN KEY (run_id) REFERENCES opticks_runs(id) ON DELETE CASCADE
    ) STRICT;

    -- Performance Indexes
    CREATE INDEX idx_events_run_id ON opticks_events(run_id);
    CREATE INDEX idx_runs_timestamp ON opticks_runs(run_timestamp);





The line ON DELETE CASCADE is an operations lifesaver. If a nightly run goes
wrong or corrupts halfway through, and you decide to drop that single row from
opticks_runs, SQLite will automatically clean up and delete all associated
event rows from opticks_events for you.


When writing your C++ parser, the workflow to populate this is a two-step process:

1. Insert your metadata into opticks_runs first.

2. Immediately retrieve the newly generated ID using
   sqlite3_last_insert_rowid(db_ptr).

3. Loop through your 2D NumPy array matrix, injecting that retrieved ID into
   the run_id column for every single row you insert into opticks_events.




Grafana querying::

    SELECT
      r.run_timestamp / 1000000 AS time,
      e.dt_simulate AS "Simulate Duration",
      r.gpu_type AS "GPU Used"
    FROM opticks_events e
    JOIN opticks_runs r ON e.run_id = r.id
    WHERE r.gpu_type = "NVIDIA RTX 4090"
    ORDER BY r.run_timestamp ASC;












versionset table
-------------------


Regarding schema for opticks monitoring - there are quite a few versions it
seems repetitive to repeat all those in the sql optricks_runs table. Perhaps
need a higher level opticks_versionset table ?

OptiXVersion:90100
ComputeCapability:89
CUDAVersion:13010
Geant4Version:1042
OpticksVersion:66


How can I get sql to only add a row when the set of versions is different ?
Also how can I get the nvidia driver version at runtime as the build time
version might differ to runtime ?







You are spot on. Moving hardware and software versions into a separate,
dedicated table is textbook database normalization. It prevents your
opticks_runs table from bloating with redundant strings or matching integer
tuples for every single nightly execution.

To make this completely seamless, you can create an opticks_versionset table
and use an INSERT OR IGNORE syntax combined with a UNIQUE constraint spanning
all five version columns. This instructs SQLite to attempt an insert, but
seamlessly drop it if that specific combination of versions already exists.

For capturing the dynamic NVIDIA Driver version at runtime, you can call the
native cudaDriverGetVersion API right before you insert your metadata.

Here is how to design and tie this all together.




::

    -- 1. High-Level Version / Hardware Configurations
    CREATE TABLE opticks_versionset (
        id                 INTEGER PRIMARY KEY AUTOINCREMENT,
        optix_version      INTEGER NOT NULL,
        compute_capability INTEGER NOT NULL,
        cuda_version       INTEGER NOT NULL,
        geant4_version     INTEGER NOT NULL,
        opticks_version    INTEGER NOT NULL,
        nvidia_driver      TEXT NOT NULL, -- Resolved at runtime

        -- This constraint guarantees uniqueness across the entire set
        UNIQUE(optix_version, compute_capability, cuda_version,
               geant4_version, opticks_version, nvidia_driver)
    ) STRICT;

    -- 2. Updated Runs Table linking back to the version set
    CREATE TABLE opticks_runs (
        id                  INTEGER PRIMARY KEY AUTOINCREMENT,
        versionset_id       INTEGER NOT NULL, -- Foreign Key to the configuration
        run_timestamp       INTEGER NOT NULL,
        fold                TEXT NOT NULL,
        script              TEXT NOT NULL,
        test                TEXT NOT NULL,
        gpu                 TEXT NOT NULL,
        geometry            TEXT NOT NULL,
        max_bounce          INTEGER NOT NULL,
        dt_geometry_load    INTEGER NOT NULL,
        dt_geometry_upload  INTEGER NOT NULL,
        total_events        INTEGER NOT NULL,

        FOREIGN KEY (versionset_id) REFERENCES opticks_versionset(id)
    ) STRICT;










