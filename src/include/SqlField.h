#ifndef SQLFIELD_H
#define SQLFIELD_H

#include "String.h"
#include "Variant.h"
#include <vector>
using std::vector;

class SqlField;
typedef vector<SqlField> SqlFieldList;

class SqlField {
    public:
        SqlField(const String &, Variant::Type, const String &);
        Variant::Type getType() const;
        String getName() const;
        String getTableName() const;
        Variant getValue() const;

        void setType(Variant::Type);
        void setName(const String &);
        void setTableName(const String &);
        void setValue(const Variant &);

    private:
        String name;
        Variant::Type type;
        String tableName;
        Variant value;

};

#endif // SQLFIELD_H