#include <sqlite3.h>
#include <iostream>

// Simple RAII wrapper for SQLite statements
struct SQLiteStmt {
    sqlite3_stmt* stmt = nullptr;
    SQLiteStmt(sqlite3* db, const char* sql) {
        sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    }
    ~SQLiteStmt() { sqlite3_finalize(stmt); }
};

void IngestJobSummary(sqlite3* db, const JobSummary& summary) {
    // Begin transaction for high performance if batch importing
    
    const char* sql = "INSERT OR REPLACE INTO jobs (job_id, job_type, timestamp, total_wall_time_ms, num_photons) VALUES (?, ?, ?, ?, ?);";
    SQLiteStmt inserter(db, sql);
    
    sqlite3_bind_text(inserter.stmt, 1, summary.job_id.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(inserter.stmt, 2, summary.job_type.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(inserter.stmt, 3, summary.timestamp.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(inserter.stmt, 4, summary.total_wall_time_ms);
    sqlite3_bind_int64(inserter.stmt, 5, summary.num_photons);
    
    if (sqlite3_step(inserter.stmt) != SQLITE_DONE) {
        std::cerr << "Failed to ingest job: " << sqlite3_errmsg(db) << std::endl;
    }
    
    // If summary.job_type == "G4GUN_INJECTION", bind and execute second statement for sub-table...
}
