#include "SqlRecord.h"
#include "SqlResult.h"

SqlResult::SqlResult() = default;

SqlRecordList SqlResult::getRecords() const {
    return records;
}

void SqlResult::setRecords(const SqlRecordList &list) {
    records = list;
}