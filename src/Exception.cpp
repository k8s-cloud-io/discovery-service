#include "Exception.h"

#include <utility>

Exception::Exception(String msg)
:message(std::move(msg)) {
}

String Exception::getMessage() const {
    return message;
}