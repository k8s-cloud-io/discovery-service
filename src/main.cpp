#include "Global.h"
#include "SqlDatabase.h"
#include "SqlQuery.h"
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

    FeedReader reader;
    FeedList feed = reader.loadFeed("https://www.n-tv.de/rss");

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
        query.bindValue(1, "feed-url");
        query.bindValue(2, "feed-title");
        query.bindValue(3, "feed-pub_date");
        query.bindValue(4, "feed-link");
        query.exec();

        db.close();

        for(FeedList::iterator it = feed.begin(); it != feed.end(); ++it) {
            cout << it->link << endl;
        }
        cout << "retrieved " << feed.size() << " feed items." << endl;
    } catch(Exception *e) {
        cout << e->getMessage() << endl;
    }
}
