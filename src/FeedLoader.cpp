#include <cstdio>
#include "CinnamonDiscovery.h"
#include "DateTime.h"
#include "FeedLoader.h"
#include "FeedReader.h"
#include "Exception.h"
#include "Logger.h"
#include "SqlDatabase.h"
#include "SqlQuery.h"

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
        SqlDatabase db = CinnamonDiscovery::getDatabase();

        // create table if not exists
        SqlQuery createTable("CREATE TABLE IF NOT EXISTS feed_item (id INTEGER PRIMARY KEY, feed_url VARCHAR(255), link VARCHAR(255), pub_date VARCHAR(255), title VARCHAR(255))", nullptr, db);
        createTable.exec();

        for(String feed: list) {
            FeedList feedItems = FeedReader::loadFeed(feed);
            
            // delete old feed items from table
            SqlQuery removeQuery("DELETE FROM feed_item WHERE feed_url = :1", "feed_item", db);
            removeQuery.bindValue(1, feed);
            removeQuery.exec();

            // insert feed items into table
            for(FeedItem item: feedItems) {
                SqlQuery insertQuery("INSERT INTO feed_item (feed_url, link, pub_date, title) VALUES(:1, :2, :3, :4)", "feed_item", db);
                insertQuery.bindValue(1, feed);
                insertQuery.bindValue(2, item.link);
                insertQuery.bindValue(3, item.pubDate);
                insertQuery.bindValue(4, item.title);
                insertQuery.exec();
            }

            Logger::log(DateTime::currentDateTime().toString() + ": FeedLoader - feed was loaded successfully");

            /*
            SqlQuery selection("SELECT pub_date FROM feed_item WHERE feed_url = :1", "feed_item", db);
            selection.bindValue(1, feed);
            selection.exec();

            auto result = selection.getResult();
            for(SqlRecord record: result->getRecords()) {
                std::cout << record.getField(0).getValue().toString() << std::endl;
            }
            delete result;
            */
        }
    } catch(const Exception &e) {
        Logger::log("Exception in class 'FeedLoader::load' - " + e.getMessage());
    }

    loading = false;
}