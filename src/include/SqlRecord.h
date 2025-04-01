#ifndef SQLRECORD_H
#define SQLRECORD_H

#include "SqlField.h"
#include "Variant.h"
#include <vector>
using std::vector;

class SqlRecord;
typedef vector<SqlRecord> SqlRecordList;

class SqlRecord {
    public:
        SqlRecord();

        SqlField getField(int) const;
        Variant getValue(int) const;
        int count() const;

        void append(const SqlField &);
        void clear();

    private:
        SqlFieldList fields;
};

#endif // SQLRECORD_H
