#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include "SqlDriver.h"
#include "String.h"

class SqlDatabase {
    public:
        enum Type {
            TYPE_NONE,
            TYPE_SQLITE
        };

        SqlDatabase();
        static SqlDatabase addDatabase(SqlDatabase::Type);

        SqlDriver *getDriver();
        bool open();
        void close();

    private:
        SqlDriver *driver;
};

#endif // SQLDATABASE_H