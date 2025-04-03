#include "SqlResult.h"
#include "SqlRecord.h"

SqlResult::SqlResult() = default;

SqlRecordList SqlResult::getRecords() const {
    return records;
}

void SqlResult::setRecords(const SqlRecordList &list) {
    records = list;
}