#ifndef FEED_LOADER_H
#define FEED_LOADER_H

#include "FeedReader.h"
#include "StringList.h"

class FeedLoader {
    public:
        FeedLoader();
        virtual ~FeedLoader();

        void load(const StringList &) const;

    private:
        FeedReader feedReader;
};

#endif