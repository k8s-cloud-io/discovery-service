#include "Exception.h"

Exception::Exception(String msg)
:message(std::move(msg)) {
}

String Exception::getMessage() const {
    return message;
}