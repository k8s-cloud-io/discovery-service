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
:SqlDriver(), db(nullptr) {

    filePath = File("sqlite3.db");
    String dir = filePath.getDirectory();
    fs::create_directories(dir.c_str());
}

bool Sqlite3Driver::open() {
    if(File::isDirectory(filePath.getAbsolutePath())) {
        throw ( string("unable to add database: path ") + filePath.getAbsolutePath() + " is a directory" );
    }

    int o = sqlite3_open(filePath.getAbsolutePath().c_str(), &db);
    setState(o == SQLITE_OK ? SqlDriver::STATE_OPEN : SqlDriver::STATE_CLOSED);

    return state() == SqlDriver::STATE_OPEN;
}

void Sqlite3Driver::close() {
    if(db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
    setState(SqlDriver::STATE_CLOSED);
}

int Sqlite3Driver::exec(const SqlQuery &q) {
    String query = q.getQuery();

    if(!isOpen()) {
        open();
    }

    if(state() != SqlDriver::STATE_OPEN) {
        throw new Exception("Unable to query database: database is not open");
    }

    int result;
    char *error = nullptr;
    if(q.getBindings().size() > 0) {
        result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if(result != SQLITE_OK) {
            throw new Exception(error ? error : String(sqlite3_errmsg(db)) + ": "  + query);
        }

        SqlBindingList bindings = q.getBindings();
        for(SqlBinding b: bindings) {
            Variant v = b.getValue();

            // TODO implement needed types for Variant's

            switch( v.getType() ) {
                case Variant::TYPE_CONST_CHAR: {
                        const char *data = v;
                        long size = std::strlen(data);
                        char *text = new char[size + 1];
                        sprintf(text, "%s", data );
                        sqlite3_bind_text(stmt, b.getPosition(), text, size, SQLITE_STATIC);
                    }
                    break;

                case Variant::TYPE_STRING: {
                        const String data = v.toString();
                        long size = data.length();
                        char *text = new char[size+1];
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
        SqlRecordList records; 
        result = sqlite3_exec(db, query.c_str(), &Sqlite3Driver::__internal_query, &records, &error);
        if(result != SQLITE_OK) {
            throw new Exception(error ? error : String(sqlite3_errmsg(db)) + ": "  + query);
        }
        close();
    }

    return SQLITE_OK;
}

int Sqlite3Driver::__internal_query(void *recordsPtr, int argc, char **argv, char **azColName) {
    (void)azColName;

    SqlRecordList *records = reinterpret_cast<SqlRecordList *>(recordsPtr);

    SqlRecord record;
    for(int i = 0; i < argc; i++) {
        SqlField field(azColName[i], Variant::TYPE_STRING, "unknown");
        field.setValue(argv[i]);
        record.append(field);
    }
    records->push_back(record);

    return 0;
 }