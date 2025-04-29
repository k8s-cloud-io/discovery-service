#ifndef FEED_LOADER_H
#define FEED_LOADER_H

#include "StringList.h"

class FeedLoader {
    public:
        FeedLoader();
        virtual ~FeedLoader();

        static void load(const StringList &);

    private:
        static bool loading;
};

#endif