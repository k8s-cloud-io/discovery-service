#include "String.h"
#include "Variant.h"

Variant::Variant()
:v(nullptr) {
}

Variant::Type Variant::getType() const {
    return type;
}

Variant::Variant(const String &val) {
    setValue(val);
    type = Variant::TYPE_STRING;
}

Variant::Variant(int val) {
    setValue(val);
    type = Variant::TYPE_INT;
}

Variant::Variant(const char *val) {
    setValue(val);
    type = Variant::TYPE_CONST_CHAR;
}

Variant::Variant(unsigned int val) {
    setValue(val);
    type = Variant::TYPE_UNSIGNED_INT;
}
Variant::Variant(float val) {
    setValue(val);
    type = Variant::TYPE_FLOAT;
}
Variant::Variant(double val) {
    setValue(val);
    type = Variant::TYPE_DOUBLE;
}

template<typename T>
void Variant::setValue(const T &value) {
    VariantClassHolder<T> *holder = new VariantClassHolder<T>();
    holder->value = value;
    v = holder;
}


