#include "SqlDatabase.h"
#include "Exception.h"

SqlDatabase::SqlDatabase()
:driver(nullptr){}

void SqlDatabase::setDriver(SqlDriver *d) {
    driver = d;
}

SqlDriver *SqlDatabase::getDriver() const {
    return driver;
}

bool SqlDatabase::open() const {
    if(driver == nullptr) {
        throw Exception("Unable to open database: driver is null");
    }

    return driver->open();
}

void SqlDatabase::close() const {
    driver->close();
}
