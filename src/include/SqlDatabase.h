#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <sqlite3.h>
#include "String.h"

class SqlDatabase {
    public:
        enum State {
            NONE,
            OPEN,
            CLOSED
        };

        static SqlDatabase addDatabase(const String &);

        void open();
        void close();
        void query(const String &);

    private:
        SqlDatabase();
        State state;
        sqlite3 *db;
        String path;
        static int __internal_query(void *, int, char **, char **);
};

#endif // SQLDATABASE_H