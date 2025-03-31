#ifndef VARIANT_H
#define VARIANT_H

#include "String.h"

template<typename T>
class VariantClassHolder {
    public:
        T value;
};

class Variant {
    public:
        Variant();
        Variant(const String &);
        Variant(const char *);
        Variant(int);
        Variant(unsigned int);
        Variant(float);
        Variant(double);

        template<typename T>
        void setValue(const T &value);

        operator String() {
            return static_cast<VariantClassHolder<String> *>(v)->value;
        }

        operator const char*() {
            return static_cast<VariantClassHolder<const char *> *>(v)->value;
        }

        operator int() {
            return reinterpret_cast<VariantClassHolder<int> *>(v)->value;
        }

        operator unsigned int() {
            return reinterpret_cast<VariantClassHolder<unsigned int> *>(v)->value;
        }

        operator float() {
            return reinterpret_cast<VariantClassHolder<float> *>(v)->value;
        }

        operator double() {
            return reinterpret_cast<VariantClassHolder<double> *>(v)->value;
        }

    private:
        void *v;
};

#endif