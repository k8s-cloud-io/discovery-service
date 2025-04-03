#ifndef SQL_RESULT_H
#define SQL_RESULT_H

#include "SqlRecord.h"

class SqlResult {
    public:
        SqlResult();

        void setRecords(const SqlRecordList &);
        [[nodiscard]] SqlRecordList getRecords() const;

    private:
        SqlRecordList records;
};

#endif // SQL_RESULT_H