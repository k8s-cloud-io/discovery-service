#ifndef SQL_DATABASE_H
#define SQL_DATABASE_H

#include "SqlDriver.h"

class SqlDatabase {
    public:
        enum Type {
            TYPE_NONE,
            TYPE_SQLITE
        };

        SqlDatabase();
        static SqlDatabase addDatabase(Type);

        SqlDriver *getDriver() const;
        bool open() const;
        void close() const;

    private:
        SqlDriver *driver;
};

#endif // SQL_DATABASE_H