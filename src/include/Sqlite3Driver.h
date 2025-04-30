#ifndef SQLITE3_DRIVER_H
#define SQLITE3_DRIVER_H

#include "sqlite3.h"
#include "File.h"
#include "SqlDriver.h"

class Sqlite3Driver final : public SqlDriver {
    public:
        Sqlite3Driver();
        virtual ~Sqlite3Driver() = default;

        void setDatabaseName(const String &) override;

        String getDatabaseName() const override;
        bool open() override;
        int exec(const SqlQuery &, const String &) override;
        String getLastError() override;
        [[nodiscard]] SqlResult *createResult() const override;

        void close() override;

    private:
        sqlite3 *db;
        sqlite3_stmt *stmt{};
        File filePath;
        SqlResult *result;
        String lastError;

        static int _internal_query(void *, int, char **, char **);
};

#endif // SQLITE3_DRIVER_H