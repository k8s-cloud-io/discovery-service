#include "Exception.h"

Exception::Exception(String msg)
:message(msg) {
}

String Exception::getMessage() const {
    return message;
}