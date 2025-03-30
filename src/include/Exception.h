#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
using std::string;

class Exception {
    public:
        explicit Exception(const string msg = nullptr);
        string getMessage() const;

    private:
        string message;
};

#endif // EXCEPTION_H