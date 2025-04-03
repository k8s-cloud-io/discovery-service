#include "SqlRecord.h"

SqlRecord::SqlRecord() = default;

SqlField SqlRecord::getField(const int index) const {
    return fields.at(index);
}

Variant SqlRecord::getValue(const int index) const {
    SqlField field = getField(index);
    return field.getValue();
}

void SqlRecord::append(const SqlField & field) {
    fields.push_back(field);
}

size_t SqlRecord::count() const {
    return fields.size();
}

void SqlRecord::clear() {
    fields.clear();
}