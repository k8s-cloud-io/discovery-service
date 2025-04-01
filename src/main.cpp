#include "Global.h"
#include "SqlDatabase.h"
#include "SqlQuery.h"
#include "SqlRecord.h"
#include "Exception.h"
#include "FeedReader.h"
#include "Variant.h"
#include "Xdg.h"

#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    string dir = Xdg::getDirectory(Xdg::XDG_PICTURES_DIR);
    cout << "DIR = " << dir << endl;

    String feedUrl = "https://www.n-tv.de/rss";
    FeedReader reader;
    FeedList feed = reader.loadFeed(feedUrl);

    try {
        SqlDatabase db = SqlDatabase::addDatabase(SqlDatabase::TYPE_SQLITE);
        SqlQuery query(
            "CREATE TABLE IF NOT EXISTS feed_item (" \
                "id INTEGER PRIMARY KEY AUTOINCREMENT," \
                "feed TEXT," \
                "title TEXT," \
                "pub_date VARCHAR(255)," \
                "link TEXT," \
                "created_at DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP" \
            ")",
            db
        );
        query.exec();

        query = SqlQuery("INSERT INTO feed_item (feed, title, pub_date, link) VALUES (?, ?, ?, ?)", db);
        for(FeedItem item: feed) {
            query.clearBindings();
            query.bindValue(1, feedUrl);
            query.bindValue(2, item.title);
            query.bindValue(3, item.pubDate);
            query.bindValue(4, item.link);
            query.exec();
        }

        query = SqlQuery("SELECT * FROM feed_item", db);
        query.exec();
        db.close();

        cout << "retrieved " << feed.size() << " feed items:" << endl;
        /*
        for(SqlRecord record: records) {
            for(int i = 0; i < record.count(); i++) {
                SqlField field = record.getField(i);
                cout << "NAME: " << field.getName() << ", TYPE: " << field.getType() <<  endl;
                cout << "VALUE: " << field.getValue().toString() << endl;
                cout << " ---------------------- END FIELD ------------------------" << endl;
            }
            cout << "-----------------------------" << endl;
        }
        */
    } catch(Exception *e) {
        cout << e->getMessage() << endl;
    }
}
