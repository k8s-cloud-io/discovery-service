#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "String.h"

class Exception {
    public:
        explicit Exception(const String &msg = nullptr);
        String getMessage() const;

    private:
        String message;
};

#endif // EXCEPTION_H