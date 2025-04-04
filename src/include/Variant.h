#ifndef VARIANT_H
#define VARIANT_H

#include "String.h"
#include "ByteArray.h"

template<typename T>
class VariantClassHolder {
    public:
        T value;
};

class Variant {
    public:
        enum Type {
            TYPE_UNKNOWN = 0,
            TYPE_BYTE_ARRAY,
            TYPE_BOOLEAN,
            TYPE_INT,
            TYPE_UNSIGNED_INT,
            TYPE_FLOAT,
            TYPE_DOUBLE,
            TYPE_CONST_CHAR,
            TYPE_STRING
        };

        Variant();
        Variant(const ByteArray &);
        Variant(const String &);
        Variant(bool);
        Variant(const char *);
        Variant(int);
        Variant(unsigned int);
        Variant(float);
        Variant(double);

        [[nodiscard]] Type getType() const;

        [[nodiscard]] String toString() const {
            return static_cast<VariantClassHolder<String> *>(v)->value;
        }

        operator ByteArray() const {
            return static_cast<VariantClassHolder<ByteArray> *>(v)->value;
        }

        operator String() const {
            return static_cast<VariantClassHolder<String> *>(v)->value;
        }

        operator const char*() const {
            return static_cast<VariantClassHolder<const char *> *>(v)->value;
        }

        operator bool() const {
            return static_cast<VariantClassHolder<bool> *>(v)->value;
        }

        operator int() const {
            return static_cast<VariantClassHolder<int> *>(v)->value;
        }

        operator unsigned int() const {
            return static_cast<VariantClassHolder<unsigned int> *>(v)->value;
        }

        operator float() const {
            return static_cast<VariantClassHolder<float> *>(v)->value;
        }

        operator double() const {
            return static_cast<VariantClassHolder<double> *>(v)->value;
        }

    private:
        template<typename T>
        void setValue(const T &value);
        void *v{};
        Type type;
};

#endif