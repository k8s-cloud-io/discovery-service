#include "Exception.h"
#include "SqlQuery.h"

SqlQuery::SqlQuery(const String &query, const String &table, const SqlDatabase &db)
:query(query), table(table), db(db), result(nullptr) {
}

void SqlQuery::bindValue(const int pos, const Variant value) {
    const SqlBinding b(pos, value);
    bindings.push_back(b);
}

void SqlQuery::exec() const {
    if(const SqlDriver *driver = db.getDriver(); driver == nullptr) {
        throw Exception("SqlQuery: driver is not initialized.");
    }
    db.getDriver()->exec(*this, table);
}

String SqlQuery::getLastError() const {
    return db.getDriver()->getLastError();
}

String SqlQuery::getQuery() const {
    return query;
}

SqlBindingList SqlQuery::getBindings() const {
    return bindings;
}

void SqlQuery::clear() {
    bindings.clear();
}

const SqlResult *SqlQuery::getResult() const {
    const SqlDriver *driver = db.getDriver();
    return driver->createResult();
}

// private access
SqlQuery::SqlQuery() = default;
