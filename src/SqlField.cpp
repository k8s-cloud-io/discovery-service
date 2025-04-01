#include "SqlField.h"

SqlField::SqlField(const String &name, Variant::Type type, const String &tableName)
:name(name), type(type), tableName(tableName) {}

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

void SqlField::setType(Variant::Type val) {
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