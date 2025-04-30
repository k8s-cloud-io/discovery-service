#ifndef BYTE_ARRAY_H
#define BYTE_ARRAY_H

#include <vector>
using std::vector;

class ByteArray: public vector<unsigned char> {
    public:
        explicit ByteArray(const size_t length = 0) {
            resize(length);
        }
        virtual ~ByteArray()= default;
        
        ByteArray &operator=(const unsigned char *a) {
            int length = 0;
            while(char ch = a[length]) {
                push_back(ch);
                length++;
            }
            return *this;
        }
};

#endif // BYTE_ARRAY_H