#include "Exception.h"

Exception::Exception(const String &msg)
:message(msg) {
}

String Exception::getMessage() const {
    return message;
}