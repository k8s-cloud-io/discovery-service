#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <vector>
using std::vector;

#include "String.h"
#include "SqlBinding.h"
#include "SqlDatabase.h"
#include "SqlRecord.h"
#include "Variant.h"

class SqlQuery {
    public:
        SqlQuery(const String &, const SqlDatabase &);
        void bindValue(int, Variant);
        int exec();
        void clearBindings() {
            bindings.clear();
        }

        String getQuery() const;
        SqlBindingList getBindings() const;

    private:
        SqlQuery();
        String query;
        SqlDatabase db;
        SqlBindingList bindings;
};

#endif // SQLQUERY_H