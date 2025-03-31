#ifndef SQLDRIVER_H
#define SQLDRIVER_H

class SqlQuery;

class SqlDriver {
    public:
        enum State {
            STATE_NONE,
            STATE_OPEN,
            STATE_CLOSED
        };

        SqlDriver();
        State state() const;

        bool isOpen() const;
        bool isClosed() const;

        virtual bool open() = 0;
        virtual void close() = 0;
        virtual int exec(const SqlQuery &) = 0;

    protected:
        void setState(SqlDriver::State);

    private:
        State driverState;
};

#endif // SQLDRIVER_H
