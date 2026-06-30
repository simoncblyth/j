opticks_monitoring_schema
==========================


Overview
----------

* try out schema and ingestion from NP array to DB in ~/np/tests/NSQLite_test.sh
* first cut of evsmry loading is working
* NEXT: run metadata and initialization timings loading - does run_meta.txt have everything needed ?


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



