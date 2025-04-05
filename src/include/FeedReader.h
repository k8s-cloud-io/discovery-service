#ifndef FEED_READER_H
#define FEED_READER_H

#include "String.h"
#include <vector>

using std::vector;

struct FeedItem {
    String pubDate;
    String title;
    String link;
};

typedef vector<FeedItem> FeedList;

class FeedReader {
    public:
        FeedReader();
        static FeedList loadFeed(const String &);
};

#endif // FEED_READER_H