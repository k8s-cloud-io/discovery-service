#include "SqlDatabase.h"
#include "Sqlite3Driver.h"

SqlDatabase::SqlDatabase()
:driver(nullptr){}

SqlDatabase SqlDatabase::addDatabase(const Type type) {
    SqlDatabase database;
    if( type == TYPE_SQLITE) {
        database.driver = new Sqlite3Driver();
    }
    return database;
}

SqlDriver *SqlDatabase::getDriver() const {
    return driver;
}

bool SqlDatabase::open() const {
    return driver->open();
}

void SqlDatabase::close() const {
    driver->close();
}
