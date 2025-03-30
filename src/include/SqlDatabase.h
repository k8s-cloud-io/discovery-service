#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <sqlite3.h>
#include <string>

using std::string;

class SqlDatabase {
    public:
        enum State {
            NONE,
            OPEN,
            CLOSED
        };

        static SqlDatabase addDatabase(const string &);

        void open();
        void close();
        void query(const string &);

    private:
        SqlDatabase();
        State state;
        sqlite3 *db;
        string path;
        static int __internal_query(void *, int, char **, char **);
};

#endif // SQLDATABASE_H