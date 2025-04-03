#ifndef SQL_QUERY_H
#define SQL_QUERY_H

#include "SqlResult.h"
#include <vector>
using std::vector;

#include "String.h"
#include "SqlBinding.h"
#include "SqlDatabase.h"
#include "Variant.h"

class SqlQuery {
    public:
        SqlQuery(String , const SqlDatabase &);
        void bindValue(int, Variant);
        int exec() const;
        void clear();

        [[nodiscard]] String getQuery() const;
        [[nodiscard]] SqlBindingList getBindings() const;
        const SqlResult *getResult() const;

    private:
        SqlQuery();
        String query;
        SqlDatabase db;
        SqlBindingList bindings;
        SqlResult *result{};
};

#endif // SQL_QUERY_H