#ifndef BYTE_ARRAY_H
#define BYTE_ARRAY_H

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

class ByteArray: public vector<char> {
    public:
        explicit ByteArray(const size_t length = 0) {
            resize(length);
        }
        ByteArray &operator=(const char *a) {
            int length = 0;
            while(char ch = a[length]) {
                push_back(ch);
                length++;
            }
            return *this;
        }
};

#endif // BYTE_ARRAY_H