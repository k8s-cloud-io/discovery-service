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

#include <iostream>
using std::cout;
using std::endl;

#include "Image.h"

int main(int argc, char *argv[]) {
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    const auto file = String("file:///home/andreas/Bilder/pawel-czerwinski-i0SaO-dWeUo-unsplash.jpg");
    const Image img = Image::fromUri(file);
    cout << "loaded file as image from path " << File(file).getFilename() << ":" << endl << "size = ";
    cout << img.getWidth();
    cout << "x";
    cout << img.getHeight() << endl;

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
        /*
        for (const auto& record : records) {
            for (size_t k = 0; k < record.count(); ++k) {
                SqlField field = record.getField(k);
                cout << field.getName()<<":"<<field.getValue().toString()<<endl;
            }
            cout << "---------------------------------------------" << endl;
        }
        */
    } catch(Exception *e) {
        cout << e->getMessage() << endl;
    }
}
