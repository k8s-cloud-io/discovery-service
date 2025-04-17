#ifndef SQL_QUERY_H
#define SQL_QUERY_H

#include <vector>
#include "SqlBinding.h"
#include "SqlDatabase.h"
#include "SqlResult.h"
#include "String.h"
#include "Variant.h"
using std::vector;

class SqlQuery {
    public:
        SqlQuery(String , const SqlDatabase &);
        void bindValue(int, Variant);
        void exec() const;
        void clear();

        [[nodiscard]] String getQuery() const;
        [[nodiscard]] SqlBindingList getBindings() const;
        [[nodiscard]] const SqlResult *getResult() const;
        [[nodiscard]] String getLastError() const;

    private:
        SqlQuery();
        String query;
        SqlDatabase db;
        SqlBindingList bindings;
        SqlResult *result{};
};

#endif // SQL_QUERY_H