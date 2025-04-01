#include "Exception.h"
#include "SqlQuery.h"
#include "Global.h"

SqlQuery::SqlQuery(const String &query, const SqlDatabase &db)
:query(query), db(db) {
}

void SqlQuery::bindValue(int pos, Variant value) {
    SqlBinding b(pos, value);
    bindings.push_back(b);
}

int SqlQuery::exec() {
    SqlDriver *driver = db.getDriver();
    if(driver == nullptr) {
        throw new Exception("SqlQuery: driver is not initialized.");
    }
    return db.getDriver()->exec(*this);
}

String SqlQuery::getQuery() const {
    return query;
}

SqlBindingList SqlQuery::getBindings() const {
    return bindings;
}

// private access
SqlQuery::SqlQuery() {}
