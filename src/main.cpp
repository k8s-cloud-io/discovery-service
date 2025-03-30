#include "Global.h"
#include "SqlDatabase.h"
#include "Exception.h"
#include "FeedReader.h"
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

    SqlDatabase db = SqlDatabase::addDatabase("./data/feed.db");
    try {
        db.open();
        db.query(
            "CREATE TABLE IF NOT EXISTS feed_item (" \
                "id AUTO_INCREMENT PRIMARY KEY," \
                "feed TEXT," \
                "title TEXT," \
                "pub_date VARCHAR," \
                "link TEXT," \
                "created_at DATETIME" \
            ")"
        );
        db.close();

        for(FeedList::iterator it = feed.begin(); it != feed.end(); ++it) {
            cout << it->link << endl;
        }
        cout << "retrieved " << feed.size() << " feed items." << endl;
    } catch(Exception *e) {
        cout << e->getMessage() << endl;
    }
}
