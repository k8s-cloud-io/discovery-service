#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "String.h"

class Exception {
    public:
        explicit Exception(String msg);
        [[nodiscard]] String getMessage() const;

    private:
        String message;
};

#endif // EXCEPTION_H