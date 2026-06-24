// ./create_db.sh

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

// Simple RAII wrapper for SQLite statements
struct SQLiteStmt
{
    sqlite3_stmt* stmt = nullptr;
    SQLiteStmt(sqlite3* db, const char* sql) {
        sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    }
    ~SQLiteStmt() { sqlite3_finalize(stmt); }
};


sqlite3* db;

//open the database
void openDB(const char* filename, sqlite3* database)
{
    int opened = sqlite3_open(filename, &database);
    if(opened){ // check if opening the database is successful
        printf("Database could not be opened %s \n", sqlite3_errmsg(database));
    } else {
        printf("opened database successfuly \n");
        db = database;
    }
}

void createTable(sqlite3* database){
    char* errMsg;
    const char* sql = "CREATE TABLE STUDENT(" 
                "ID INT PRIMARY KEY NOT NULL,"
                "FIRST_NAME TEXT NOT NULL,"
                "LAST_NAME TEXT NOT NULL,"
                "EMAIL TEXT NOT NULL)";

    int rc = sqlite3_exec(database, sql, NULL, 0, &errMsg);
    if(rc != SQLITE_OK){
        printf("Error in executing SQL: %s \n", errMsg);
        //free the error message
        sqlite3_free(errMsg);
    } else {
        printf("table STUDENT made successfully");
    }
}


void insertData(sqlite3* db){
    char* errMsg;
    const char* sql = "INSERT INTO STUDENT (ID, FIRST_NAME, LAST_NAME, EMAIL) "
                "VALUES(1, 'John', 'Doe', 'john@doe.com'),"
                "(2, 'Peter', 'Griffin', 'peter@griffin.com'),"
                "(3, 'Homer', 'Simpson', 'homer@simpson.com')";

    int rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    if(rc != SQLITE_OK) {
        printf("error occured %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("operation insert successful \n");
    }
}

void addStudent(sqlite3* db, int id, const char* first_name, const char* last_name, const char* email )
{
    const char* sql = "INSERT OR REPLACE INTO STUDENT (ID, FIRST_NAME, LAST_NAME, EMAIL) VALUES (?, ?, ?, ?);";
    SQLiteStmt inserter(db, sql);

    sqlite3_bind_int64(inserter.stmt, 1, id);
    sqlite3_bind_text(inserter.stmt, 2, first_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(inserter.stmt, 3, last_name,  -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(inserter.stmt, 4, email,      -1, SQLITE_TRANSIENT);

    if (sqlite3_step(inserter.stmt) != SQLITE_DONE) {
        std::cerr << "Failed to ingest student: " << sqlite3_errmsg(db) << std::endl;
    }
}



void readStudentColumns(sqlite3* db)
{
    const char* sql = "SELECT * FROM 'STUDENT'; ";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(rc != SQLITE_OK)
    {
        printf("error occurred: %s", sqlite3_errmsg(db));
    }
    else
    {
        int NoOfCols = sqlite3_column_count(stmt); //get the number of columns in the table
        printf("NoOfCols: %d", NoOfCols);
        for(int i=0; i<NoOfCols; i++){ //iterate through the columns and get data for each column
                    const  char* colName =  sqlite3_column_name(stmt, i); //get the column name
                    printf("colName: %s\n", colName);
                }
    }
}



int callback(void *data, int count, char **argv, char **columnNames){
    //1st parameter of this function is received from 4th parameter of sqlite3_exec
    //count -> is the number of columns
    //columnNames ->  array of pointers to strings where each entry represents the name of corresponding result column as obtained
    //argv -> array of pointers to strings obtained as if from [sqlite3_column_text()]

   int i;
   for(i = 0; i<count; i++) {
      printf("Col: %s = %s\n", columnNames[i], argv[i]);
   }
   printf("\n");
   return 0;
}


void readData(sqlite3* db)
{
    char* errMsg = 0;
    const char* sql = "SELECT * FROM 'STUDENT'";

    int rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if(rc != SQLITE_OK){
        printf("Error in executing SQL: %s \n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("read data successfully \n");
    }
}



int main(int, char**)
{
    const char* filename = "/tmp/db.sqlite3";
    openDB(filename,  db);
    createTable(db);
    insertData(db);
    addStudent(db, 4, "Peter", "Parker", "peter@batcave.com" );
    readStudentColumns(db);
    readData(db);
}

