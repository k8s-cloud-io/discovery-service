#include "Exception.h"
#include "SqlField.h"
#include "Sqlite3Driver.h"
#include "SqlQuery.h"
#include "SqlRecord.h"

#include <cstring>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;
using std::cout;
using std::endl;

Sqlite3Driver::Sqlite3Driver()
:SqlDriver(), db(nullptr), result(nullptr) {

    filePath = File("sqlite3.db");
    const String dir = filePath.getDirectory();
    fs::create_directories(dir.c_str());
}

bool Sqlite3Driver::open() {
    if(File::isDirectory(filePath.getAbsolutePath())) {
        throw ( string("unable to add database: path ") + filePath.getAbsolutePath() + " is a directory" );
    }

    int o = sqlite3_open(filePath.getAbsolutePath().c_str(), &db);
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

int Sqlite3Driver::exec(const SqlQuery &q) {
    const String query = q.getQuery();

    if(!isOpen()) {
        open();
    }

    if(state() != STATE_OPEN) {
        throw new Exception("Unable to query database: database is not open");
    }

    int rc;
    char *error = nullptr;
    if(q.getBindings().size() > 0) {
        rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK) {
            throw new Exception((error ? error : String(sqlite3_errmsg(db)) + ": "  + query).data());
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
                        sqlite3_bind_text(stmt, b.getPosition(), text, size, SQLITE_STATIC);
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
                    throw new Exception("unable to bind parameter: invalid Variant type");
            }

            // bind blob values
        }
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        close();
    }
    else {
        result = new SqlResult();
        SqlRecordList records;
        rc = sqlite3_exec(db, query.c_str(), &Sqlite3Driver::_internal_query, &records, &error);
        if(rc != SQLITE_OK) {
            throw new Exception((error ? error : String(sqlite3_errmsg(db)) + ": "  + query).data());
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