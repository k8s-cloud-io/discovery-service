#include "SqlField.h"

SqlField::SqlField(String name, const Variant::Type type, String tableName)
:name(std::move(name)), type(type), tableName(std::move(tableName)) {}

Variant::Type SqlField::getType() const {
    return type;
}

String SqlField::getName() const {
    return name;
}

String SqlField::getTableName() const {
    return tableName;
}

Variant SqlField::getValue() const {
    return value;
}

void SqlField::setType(const Variant::Type val) {
    type = val;
}

void SqlField::setName(const String &val) {
    name = val;
}

void SqlField::setTableName(const String &val) {
    tableName = val;
}

void SqlField::setValue(const Variant &val) {
    value = val;
}