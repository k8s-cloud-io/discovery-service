#ifndef BYTEARRY_H
#define BYTEARRY_H

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

class ByteArray: public vector<char> {
    public:
        ByteArray &operator=(const char *a) {
            int length = 0;
            while(char ch = a[length]) {
                push_back(ch);
                length++;
            }

            cout << size() << endl;

            return *this;
        }
};

#endif // BYTEARRY_H