#ifndef SQLITE3DRIVER_H
#define SQLITE3DRIVER_H

#include "sqlite3.h"
#include "File.h"
#include "SqlDriver.h"

class Sqlite3Driver: public SqlDriver {
    public:
        Sqlite3Driver();
        bool open();
        int exec(const SqlQuery &);

        void close();

    private:
        sqlite3 *db;
        sqlite3_stmt *stmt;
        File filePath;

        static int __internal_query(void *, int, char **, char **);
};

#endif // SQLITE3DRIVER_H