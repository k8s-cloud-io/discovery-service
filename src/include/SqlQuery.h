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