#include "String.h"
#include "Variant.h"

Variant::Variant()
:v(nullptr) ,type(TYPE_UNKNOWN){
}

Variant::Type Variant::getType() const {
    return type;
}

Variant::Variant(const ByteArray &val) {
    setValue(val);
    type = TYPE_BYTE_ARRAY;
}

Variant::Variant(const String &val) {
    setValue(val);
    type = TYPE_STRING;
}

Variant::Variant(const int val) {
    setValue(val);
    type = TYPE_INT;
}

Variant::Variant(const bool val) {
    setValue(val);
    type = TYPE_BOOLEAN;
}

Variant::Variant(const char *val) {
    setValue(val);
    type = TYPE_CONST_CHAR;
}

Variant::Variant(const unsigned int val) {
    setValue(val);
    type = TYPE_UNSIGNED_INT;
}
Variant::Variant(const float val) {
    setValue(val);
    type = TYPE_FLOAT;
}
Variant::Variant(const double val) {
    setValue(val);
    type = TYPE_DOUBLE;
}

template<typename T>
void Variant::setValue(const T &value) {
    auto *holder = new VariantClassHolder<T>();
    holder->value = value;
    v = holder;
}


