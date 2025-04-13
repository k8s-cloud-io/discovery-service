#include <File.h>

#include "Global.h"

#include "SqlDatabase.h"
#include "SqlQuery.h"
#include "SqlRecord.h"
#include "Exception.h"
#include "FeedReader.h"
#include "Variant.h"
#include "Xdg.h"

#include "ByteArray.h"

#include <atomic>
#include <iostream>
using std::cout;
using std::endl;

#include "Image.h"
#include "User.h"
#include "Timer.h"
#include "Application.h"
#include <atomic>

#include "UserSettings.h"
#include "DateTime.h"

class InlineClass {
    public:
        Timer t;
        int count = 0;
        void start() {
            t.setInterval(1000);
            t.start([this](Timer *) {
                cout << "timer event: " << count << endl;
                count++;
            });
        }
};

int main(const int argc, char *argv[]) {
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    Application app;

    UserSettings settings;

    /*
    InlineClass i;
    i.start();
    */

    /*
    DateTime dt = DateTime::fromString("2025-05-04 12:28:00", "%Y-%m-%d %H:%M:%S");
    std::cout << dt.toString() << endl;
    std::cout << "CUSTOM STRING: " << dt.toString("%d.%m.%Y %H:%M:%S") << endl;

    dt.addDays(40);
    std::cout << "ADD 40 DAYS: " << dt.toString() << endl;

    dt.addHours(4);
    std::cout << "ADD 4 HOURS: " << dt.toString() << endl;

    dt.addMinutes(3);
    std::cout << "ADD 3 Minutes: " << dt.toString() << endl;
    */

    return app.start();

    /*
    const auto file = String("file:///home/andreas/Bilder/pawel-czerwinski-i0SaO-dWeUo-unsplash.jpg");
    const Image img = Image::fromUri(file);
    cout << "loaded file as image from path " << File(file).getFilename() << ":" << endl << "size = ";
    cout << img.getWidth();
    cout << "x";
    cout << img.getHeight() << endl;
    */

    /*
    const User current = User::current();
    cout << "User: " << current.getId() << endl;
    cout << "Name: " << current.getName() << endl;
    cout << "Home: " << current.getHomeDirectory() << endl;
    cout << "Documents: " << current.getDirectory(XDG_DOCUMENTS_DIR) << endl;
    cout << "Downloads: " << current.getDirectory(XDG_DOWNLOAD_DIR) << endl;
    cout << "Pictures: " << current.getDirectory(XDG_PICTURES_DIR) << endl;
    cout << "Music: " << current.getDirectory(XDG_MUSIC_DIR) << endl;
    cout << "Videos: " << current.getDirectory(XDG_VIDEOS_DIR) << endl;
    */

    /*
    const string dir = Xdg::getDirectory(Xdg::XDG_PICTURES_DIR);
    cout << dir << endl;

    const String feedUrl = "https://www.n-tv.de/rss";
    FeedList feed = FeedReader::loadFeed(feedUrl);

    try {
        const SqlDatabase db = SqlDatabase::addDatabase(SqlDatabase::TYPE_SQLITE);

        const auto query = SqlQuery("SELECT * FROM feed_item", db);
        query.exec();

        const SqlRecordList records = query.getResult()->getRecords();
        db.close();

        cout << "retrieved " << records.size() << " feed items" << endl;
        for (const auto& record : records) {
            for (size_t k = 0; k < record.count(); ++k) {
                SqlField field = record.getField(k);
                cout << field.getName()<<":"<<field.getValue().toString()<<endl;
            }
            cout << "---------------------------------------------" << endl;
        }
    } catch(const Exception &e) {
        cout << e.getMessage() << endl;
    }
    */
}
