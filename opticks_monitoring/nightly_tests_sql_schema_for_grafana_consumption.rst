nightly_tests_sql_schema_for_grafana_consumption.rst
=====================================================


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




