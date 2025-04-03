#include "SqlBinding.h"

SqlBinding::SqlBinding(const int pos, const Variant value)
:pos(pos), value(value) {}

int SqlBinding::getPosition() const {
    return pos;
}

Variant SqlBinding::getValue() const {
    return value;
}