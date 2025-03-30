#ifndef FEEDREADER_H
#define FEEDREADER_H

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
        FeedList loadFeed(const String &);
};

#endif // FEEDREADER_H