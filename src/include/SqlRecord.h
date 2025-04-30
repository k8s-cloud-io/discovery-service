#ifndef SQL_RECORD_H
#define SQL_RECORD_H

#include <vector>
#include "SqlField.h"
#include "Variant.h"
using std::vector;

class SqlRecord;
typedef vector<SqlRecord> SqlRecordList;

class SqlRecord {
    public:
        SqlRecord();
        virtual ~SqlRecord() = default;

        [[nodiscard]] SqlField getField(int) const;
        [[nodiscard]] Variant getValue(int) const;
        [[nodiscard]] size_t count() const;

        void append(const SqlField &);
        void clear();

    private:
        SqlFieldList fields;
};

#endif // SQL_RECORD_H
