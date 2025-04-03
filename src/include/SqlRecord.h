#ifndef SQL_RECORD_H
#define SQL_RECORD_H

#include "SqlField.h"
#include "Variant.h"
#include <vector>
using std::vector;

class SqlRecord;
typedef vector<SqlRecord> SqlRecordList;

class SqlRecord {
    public:
        SqlRecord();

        [[nodiscard]] SqlField getField(int) const;
        [[nodiscard]] Variant getValue(int) const;
        [[nodiscard]] size_t count() const;

        void append(const SqlField &);
        void clear();

    private:
        SqlFieldList fields;
};

#endif // SQL_RECORD_H
