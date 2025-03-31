#ifndef SQLBINDING_H
#define SQLBINDING_H

#include "Variant.h"
#include <vector>

class SqlBinding {
    public:
        SqlBinding(int, Variant);
        Variant getValue() const;
        int getPosition() const;

    private:
        int pos;
        Variant value;
};

typedef std::vector<SqlBinding> SqlBindingList;

#endif // SQLBINDING_H
