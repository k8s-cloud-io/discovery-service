#include "SqlRecord.h"

SqlRecord::SqlRecord() {}

SqlField SqlRecord::getField(int index) const {
    return fields.at(index);
}

Variant SqlRecord::getValue(int index) const {
    SqlField field = getField(index);
    return field.getValue();
}

void SqlRecord::append(const SqlField & field) {
    fields.push_back(field);
}

int SqlRecord::count() const {
    return fields.size();
}

void SqlRecord::clear() {
    fields.clear();
}