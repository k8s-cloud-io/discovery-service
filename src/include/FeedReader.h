#ifndef FEED_READER_H
#define FEED_READER_H

#include <vector>
#include "String.h"
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
        virtual ~FeedReader() = default;
        static FeedList loadFeed(const String &);
};

#endif // FEED_READER_H