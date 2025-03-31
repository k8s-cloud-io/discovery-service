#include "SqlBinding.h"

SqlBinding::SqlBinding(int pos, Variant value)
:pos(pos), value(value) {}

int SqlBinding::getPosition() const {
    return pos;
}

Variant SqlBinding::getValue() const {
    return value;
}