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
