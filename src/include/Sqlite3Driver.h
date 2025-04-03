#ifndef SQLITE3_DRIVER_H
#define SQLITE3_DRIVER_H

#include "sqlite3.h"
#include "File.h"
#include "SqlDriver.h"

class Sqlite3Driver: public SqlDriver {
    public:
        Sqlite3Driver();
        bool open() override;
        int exec(const SqlQuery &) override;
        [[nodiscard]] SqlResult *createResult() const override;

        void close() override;

    private:
        sqlite3 *db;
        sqlite3_stmt *stmt{};
        File filePath;
        SqlResult *result;

        static int _internal_query(void *, int, char **, char **);
};

#endif // SQLITE3_DRIVER_H