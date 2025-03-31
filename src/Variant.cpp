#include "String.h"
#include "Variant.h"

Variant::Variant()
:v(nullptr) {
}

Variant::Variant(const String &val) {
    setValue(val);
}

Variant::Variant(int val) {
    setValue(val);
}

Variant::Variant(const char *val) {
    setValue(val);
}

Variant::Variant(unsigned int val) {
    setValue(val);
}
Variant::Variant(float val) {
    setValue(val);
}
Variant::Variant(double val) {
    setValue(val);
}

template<typename T>
void Variant::setValue(const T &value) {
    VariantClassHolder<T> *holder = new VariantClassHolder<T>();
    holder->value = value;
    v = holder;
}


