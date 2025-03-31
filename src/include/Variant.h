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
        enum Type {
            TYPE_UNKNOWN = 0,
            TYPE_INT,
            TYPE_UNSIGNED_INT,
            TYPE_FLOAT,
            TYPE_DOUBLE,
            TYPE_CONST_CHAR,
            TYPE_STRING
        };

        Variant();
        Variant(const String &);
        Variant(const char *);
        Variant(int);
        Variant(unsigned int);
        Variant(float);
        Variant(double);

        Type getType() const;

        String toString() {
            return reinterpret_cast<VariantClassHolder<String> *>(v)->value;
        }

        operator String() const {
            return reinterpret_cast<VariantClassHolder<String> *>(v)->value;
        }

        operator const char*() {
            return reinterpret_cast<VariantClassHolder<const char *> *>(v)->value;
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
        template<typename T>
        void setValue(const T &value);
        void *v;
        Type type;
};

#endif