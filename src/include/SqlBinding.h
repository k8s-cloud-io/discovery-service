#ifndef SQL_BINDING_H
#define SQL_BINDING_H

#include "Variant.h"
#include <vector>

class SqlBinding {
    public:
        SqlBinding(int, Variant);
        [[nodiscard]] Variant getValue() const;
        [[nodiscard]] int getPosition() const;

    private:
        int pos;
        Variant value;
};

typedef std::vector<SqlBinding> SqlBindingList;

#endif // SQL_BINDING_H
