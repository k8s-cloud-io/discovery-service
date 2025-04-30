#ifndef LOGGER_H
#define LOGGER_H

#include "String.h"

class Logger {
    public:
        virtual ~Logger(){}
        static void log(const String &);

    private:
        Logger(){}
};

#endif // LOGGER_H