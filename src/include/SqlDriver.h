#ifndef SQL_DRIVER_H
#define SQL_DRIVER_H

#include "String.h"

class SqlQuery;
class SqlResult;

class SqlDriver {
    public:
        enum State {
            STATE_NONE = 0,
            STATE_OPEN,
            STATE_CLOSED
        };

        SqlDriver();
        virtual ~SqlDriver() = default;
        
        [[nodiscard]] State state() const;

        [[nodiscard]] bool isOpen() const;
        [[nodiscard]] bool isClosed() const;

        virtual void setDatabaseName(const String &) = 0;
        virtual String getDatabaseName() const = 0;
        virtual String getLastError() = 0;
        virtual bool open() = 0;
        virtual void close() = 0;
        [[nodiscard]] virtual SqlResult *createResult() const = 0;
        virtual int exec(const SqlQuery &, const String &) = 0;

    protected:
        void setState(State);

    private:
        State driverState;
};

#endif // SQL_DRIVER_H
