//#include "SqlDatabase.h"
//#include "Exception.h"
//#include "FeedReader.h"
#include "Xdg.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string dir = Xdg::getDirectory(Xdg::XDG_DESKTOP_DIR);
    cout << "DIR = " << dir << endl;
    return 0;

    /*
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
    */
}
