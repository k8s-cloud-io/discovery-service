#ifndef SQL_DRIVER_H
#define SQL_DRIVER_H

class SqlQuery;
class SqlResult;

class SqlDriver {
    public:
        virtual ~SqlDriver() = default;

        enum State {
            STATE_NONE = 0,
            STATE_OPEN,
            STATE_CLOSED
        };

        SqlDriver();
        [[nodiscard]] State state() const;

        [[nodiscard]] bool isOpen() const;
        [[nodiscard]] bool isClosed() const;

        virtual bool open() = 0;
        virtual void close() = 0;
        [[nodiscard]] virtual SqlResult *createResult() const = 0;
        virtual int exec(const SqlQuery &) = 0;

    protected:
        void setState(SqlDriver::State);

    private:
        State driverState;
};

#endif // SQL_DRIVER_H
