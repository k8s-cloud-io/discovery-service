#ifndef SQL_FIELD_H
#define SQL_FIELD_H

#include <vector>
#include "String.h"
#include "Variant.h"
using std::vector;

class SqlField;
typedef vector<SqlField> SqlFieldList;

class SqlField {
    public:
        SqlField(String , Variant::Type, String );
        virtual ~SqlField() = default;

        [[nodiscard]] Variant::Type getType() const;
        [[nodiscard]] String getName() const;
        [[nodiscard]] String getTableName() const;
        [[nodiscard]] Variant getValue() const;

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

#endif // SQL_FIELD_H