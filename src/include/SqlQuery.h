#ifndef SQLQUERY_H
#define SQLQUERY_H

#include "SqlResult.h"
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
        int exec();
        void clear();

        String getQuery() const;
        SqlBindingList getBindings() const;
        const SqlResult *getResult();

    private:
        SqlQuery();
        String query;
        SqlDatabase db;
        SqlBindingList bindings;
        SqlResult *result;
};

#endif // SQLQUERY_H