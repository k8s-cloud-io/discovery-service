#ifndef SQL_BINDING_H
#define SQL_BINDING_H

#include <vector>
#include "Variant.h"
using std::vector;

class SqlBinding {
    public:
        SqlBinding(int, Variant);
        virtual ~SqlBinding() = default;

        [[nodiscard]] Variant getValue() const;
        [[nodiscard]] int getPosition() const;

    private:
        int pos;
        Variant value;
};

typedef vector<SqlBinding> SqlBindingList;

#endif // SQL_BINDING_H
