#include <cstring>
#include <filesystem>
#include "Exception.h"
#include "SqlField.h"
#include "Sqlite3Driver.h"
#include "SqlQuery.h"
#include "SqlRecord.h"
#include "Variant.h"
namespace fs = std::filesystem;

Sqlite3Driver::Sqlite3Driver()
:db(nullptr), result(nullptr) {
}

void Sqlite3Driver::setDatabaseName(const String &name) {
    filePath = File(name);
    const String dir = filePath.getDirectory();
    if(!fs::is_directory(fs::path(dir.c_str()))) {
        fs::create_directories(dir.c_str());
    }
}

String Sqlite3Driver::getDatabaseName() const {
    return filePath.getAbsolutePath();
}

bool Sqlite3Driver::open() {
    if(filePath.getFilename().empty()) {
        throw Exception("unable to add database: path is empty");
    }

    if(File::isDirectory(filePath.getAbsolutePath())) {
        throw Exception(( String("unable to add database: path ") + filePath.getAbsolutePath() + " is a directory" ));
    }

    const int o = sqlite3_open(filePath.getAbsolutePath().c_str(), &db);
    setState(o == SQLITE_OK ? STATE_OPEN : STATE_CLOSED);

    return state() == STATE_OPEN;
}

void Sqlite3Driver::close() {
    if(db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
    setState(STATE_CLOSED);
}

int Sqlite3Driver::exec(const SqlQuery &q, const String &table) {
    if(!isOpen()) {
        open();
    }

    if(state() != STATE_OPEN) {
        throw Exception("Unable to query database: database is not open");
    }

    int rc;
    char *error = nullptr;

    String query = q.getQuery();
    result = new SqlResult();

    if(q.getBindings().size() > 0) {
        rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, const_cast<const char **>(&error));
        if(rc != SQLITE_OK) {
            throw Exception((error ? error : String(sqlite3_errmsg(db)) + ": "  + query).data());
        }

        SqlBindingList bindings = q.getBindings();
        for(SqlBinding b: bindings) {
            // TODO implement needed types for Variant's

            switch(Variant v = b.getValue(); v.getType() ) {
                case Variant::TYPE_CONST_CHAR: {
                        const char *data = v;
                        const size_t size = std::strlen(data);
                        const auto text = new char[size + 1];
                        sprintf(text, "%s", data );
                        sqlite3_bind_text(stmt, b.getPosition(), text, static_cast<int>(size), SQLITE_STATIC);
                    }
                    break;

                case Variant::TYPE_STRING: {
                        const String data = v.toString();
                        const int size = static_cast<int>(data.length());
                        auto *text = new char[size+1];
                        sprintf(text, "%s", data.c_str() );
                        sqlite3_bind_text(stmt, b.getPosition(), text, size, SQLITE_STATIC);
                    }
                    break;

                /*
                case Variant::TYPE_INT: {
                        int i = v;
                        sqlite3_bind_int(stmt, b.getPosition(), i);
                    }
                    break;

                case Variant::TYPE_UNSIGNED_INT: {
                        unsigned int i = v;
                        sqlite3_bind_int(stmt, b.getPosition(), i);
                    }
                    break;

                case Variant::TYPE_FLOAT: {
                        float i = v;
                        sqlite3_bind_int(stmt, b.getPosition(), i);
                    }
                    break;

                case Variant::TYPE_DOUBLE: {
                        double i = v;
                        sqlite3_bind_int(stmt, b.getPosition(), i);
                    }
                    break;
                */
                    
                default:
                    throw Exception("unable to bind parameter: invalid Variant type");
            }

            // bind blob values
        }
        
        try {
            int cols = sqlite3_column_count(stmt);
            String col_name;
            String col_value;

            SqlRecordList records;
            while(sqlite3_step(stmt) == SQLITE_ROW) {
                SqlRecord record;
                for (int i=0;i<cols;i++) {
                    if (sqlite3_column_name(stmt,i))
                        col_name = sqlite3_column_name(stmt,i);
                
                    if (sqlite3_column_text(stmt,i))
                        col_value = reinterpret_cast<const char *>(sqlite3_column_text(stmt,i));

                    SqlField field(col_name, Variant::TYPE_STRING, table);
                    field.setValue(col_value);
                    record.append(field);
                }
                records.push_back(record);
            }
            result->setRecords(records);
            sqlite3_finalize(stmt);
        }
        catch(const Exception &e) {
            throw Exception(e);
        }
        close();
    }
    else {
        result = new SqlResult();
        SqlRecordList records;
        try {
            rc = sqlite3_exec(db, query.c_str(), &Sqlite3Driver::_internal_query, &records, &error);
            if(rc != SQLITE_OK) {
                lastError = String(sqlite3_errmsg(db));
                throw Exception((error ? error : String(sqlite3_errmsg(db)) + ": "  + query).data());
            }
        } catch(const Exception &e) {
            throw Exception(e);
        }
        result->setRecords(records);
        close();
    }

    return SQLITE_OK;
}

SqlResult *Sqlite3Driver::createResult() const {
    return result;
}

int Sqlite3Driver::_internal_query(void *recordsPtr, const int argc, char **argv, char **azColName) {
    (void)azColName;

    auto *records = static_cast<SqlRecordList *>(recordsPtr);

    SqlRecord record;
    for(int i = 0; i < argc; i++) {
        SqlField field(String(azColName[i]), Variant::TYPE_STRING, String("unknown"));
        field.setValue(Variant(String(argv[i])));
        record.append(field);
    }
    records->push_back(record);
    return 0;
}

String Sqlite3Driver::getLastError() {
    return lastError;
}