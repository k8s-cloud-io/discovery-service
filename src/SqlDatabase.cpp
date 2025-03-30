#include <exception>
#include <filesystem>
#include <sqlite3.h>

#include "Dir.h"
#include "File.h"
#include "Exception.h"
#include "SqlDatabase.h"

#include <iostream>
using std::cout;
using std::endl;

namespace fs = std::filesystem;

SqlDatabase SqlDatabase::addDatabase(const string &path) {
    if(File::isDirectory(path)) {
        throw ( string("unable to add database: path ") + path + " is a directory" );
    }

    File file(path);
    string dir = file.getDirectory();
    fs::create_directories(dir);

    SqlDatabase database;
    database.path = path;
    return database;
}

void SqlDatabase::open() {
    int o = sqlite3_open(path.c_str(), &db);
    state = o == SQLITE_OK ? SqlDatabase::OPEN : SqlDatabase::CLOSED;
}

void SqlDatabase::query(const string &q) {
    if(state != SqlDatabase::OPEN) {
        throw new Exception("Unable to query database: database is not open");
    }

    char *error = nullptr;
    void *columns;
    int result = sqlite3_exec(db, q.c_str(), &SqlDatabase::__internal_query, &columns, &error);
    if(result != SQLITE_OK) {
        throw new Exception(error ? error : "unknown sql error in query: "  + q);
    }
}

void SqlDatabase::close() {
    if(db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
    state = SqlDatabase::CLOSED;
}

// private
SqlDatabase::SqlDatabase()
:state(SqlDatabase::NONE), db(nullptr) {
}

int SqlDatabase::__internal_query(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
 }