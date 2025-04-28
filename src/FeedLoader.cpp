#include "FeedLoader.h"
#include "Exception.h"
#include "SqlDatabase.h"
#include "Sqlite3Driver.h"
#include "User.h"
#include <iostream>

FeedLoader::FeedLoader() {
}

FeedLoader::~FeedLoader(){}

void FeedLoader::load(const StringList &list) const {
    try {
        User u = User::current();
        String databasePath = u.getDirectory(XDG_DOCUMENTS_DIR).append("/cinnamon-discovery");
        databasePath = databasePath.append("/discovery.db");

        SqlDatabase db;
        auto driver = new Sqlite3Driver();
        driver->setDatabaseName(databasePath);
        db.setDriver(driver);

        // TODO create table if not exists

        for(String feed: list) {
            FeedList feedItems = feedReader.loadFeed(feed);
            // TODO remove old feed items related to url
            // TODO insert feed items into database
        }
    } catch(const Exception &e) {
        std::cout << "ERROR in FeedLoader::load - " << e.getMessage() << std::endl;
    }
}