#ifndef SQLRESULT_H
#define SQLRESULT_H

#include "SqlRecord.h"

class SqlResult {
    public:
        SqlResult();

        void setRecords(const SqlRecordList &);
        SqlRecordList getRecords() const;

    private:
        SqlRecordList records;
};

#endif // SQLRESULT_H