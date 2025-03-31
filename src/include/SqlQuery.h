#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <vector>
using std::vector;

#include "String.h"
#include "SqlBinding.h"
#include "SqlDatabase.h"
#include "Variant.h"

class SqlQuery {
    public:
        SqlQuery(const String &, const SqlDatabase &);
        void bindValue(int, Variant);
        void exec();

        String getQuery() const;
        SqlBindingList getBindings() const;

    private:
        SqlQuery();
        String query;
        SqlDatabase db;
        SqlBindingList bindings;
};

#endif // SQLQUERY_H