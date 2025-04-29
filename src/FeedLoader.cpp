#include <cstdio>
#include <iostream>
#include "FeedLoader.h"
#include "FeedReader.h"
#include "Exception.h"
#include "SqlDatabase.h"
#include "SqlQuery.h"
#include "SqlRecord.h"
#include "Sqlite3Driver.h"
#include "User.h"

bool FeedLoader::loading = false;

FeedLoader::FeedLoader() {
}

FeedLoader::~FeedLoader(){}

void FeedLoader::load(const StringList &list) {
    if(loading) {
        return;
    }

    loading = true;
    try {
        User u = User::current();
        String databasePath = u.getDirectory(XDG_DOCUMENTS_DIR).append("/cinnamon-discovery");
        databasePath = databasePath.append("/discovery.db");

        SqlDatabase db;
        auto driver = new Sqlite3Driver();
        driver->setDatabaseName(databasePath);
        db.setDriver(driver);

        // create table if not exists
        SqlQuery createTable("CREATE TABLE IF NOT EXISTS feed_item (id INTEGER PRIMARY KEY, feed_url VARCHAR(255), link VARCHAR(255), pub_date VARCHAR(255), title VARCHAR(255))", db);
        createTable.exec();

        for(String feed: list) {
            std::cout << "load feed " << feed << std::endl;
            FeedList feedItems = FeedReader::loadFeed(feed);
            
            SqlQuery removeQuery("DELETE FROM feed_item WHERE feed_url = :1", db);
            removeQuery.bindValue(1, feed);
            removeQuery.exec();

            for(FeedItem item: feedItems) {
                SqlQuery insertQuery("INSERT INTO feed_item (feed_url, link, pub_date, title) VALUES(:1, :2, :3, :4)", db);
                insertQuery.bindValue(1, feed);
                insertQuery.bindValue(2, item.link);
                insertQuery.bindValue(3, item.pubDate);
                insertQuery.bindValue(4, item.title);
                insertQuery.exec();

                std::cout << item.title << std::endl;
            }

            SqlQuery selection("SELECT * FROM feed_item WHERE feed_url = :1", db);
            selection.bindValue(1, feed);
            selection.exec();
            auto result = selection.getResult();
            for(SqlRecord record: result->getRecords()) {
                std::cout << record.getField(0).getValue().toString() << std::endl;
            }
            std::cout << "got feed items: raw = " << feedItems.size() << ", inserted = " << result->getRecords().size() << std::endl;
            delete result;

            // TODO insert feed items into database
        }
    } catch(const Exception &e) {
        std::cout << e.what() << " in class 'FeedLoader::load' - " << e.getMessage() << std::endl;
    }

    loading = false;
}