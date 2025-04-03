#include "Global.h"
/*
#include "SqlDatabase.h"
#include "SqlQuery.h"
#include "SqlRecord.h"
#include "Exception.h"
#include "FeedReader.h"
#include "Variant.h"
#include "Xdg.h"
*/

#include <iostream>
using std::cout;
using std::endl;

#include "Image.h"

int main(int argc, char *argv[]) {
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    Image img = Image::fromUri("https://wallpapers.com/images/hd/aesthetic-easter-eggs-and-purple-flowers-20vibq9er4gi649w.jpg");
    img.scale(640, 480);
    /*
    string dir = Xdg::getDirectory(Xdg::XDG_PICTURES_DIR);

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
            query.clear();
            query.bindValue(1, feedUrl);
            query.bindValue(2, item.title);
            query.bindValue(3, item.pubDate);
            query.bindValue(4, item.link);
            query.exec();
        }

        query = SqlQuery("SELECT * FROM feed_item", db);
        query.exec();
        SqlRecordList records = query.getResult()->getRecords();
        db.close();

        cout << "retrieved " << records.size() << " feed items:" << endl;
    } catch(Exception *e) {
        cout << e->getMessage() << endl;
    }
    */
}
