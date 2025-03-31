#include "SqlDatabase.h"
#include "Sqlite3Driver.h"

SqlDatabase::SqlDatabase()
:driver(nullptr){}

SqlDatabase SqlDatabase::addDatabase(SqlDatabase::Type type) {
    SqlDatabase database;
    if( type == SqlDatabase::TYPE_SQLITE) {
        database.driver = new Sqlite3Driver();
    }
    return database;
}

SqlDriver *SqlDatabase::getDriver() {
    return driver;
}

bool SqlDatabase::open() {
    return driver->open();
}

void SqlDatabase::close() {
    driver->close();
}
