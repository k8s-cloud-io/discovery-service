#ifndef SQL_DATABASE_H
#define SQL_DATABASE_H

#include "SqlDriver.h"

class SqlDatabase {
    public:
        SqlDatabase();

        void setDriver(SqlDriver *);
        void close() const;

        [[nodiscard]] SqlDriver *getDriver() const;
        [[nodiscard]] bool open() const;

    private:
        SqlDriver *driver;
};

#endif // SQL_DATABASE_H