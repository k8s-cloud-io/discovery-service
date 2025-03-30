#ifndef FEEDREADER_H
#define FEEDREADER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

struct FeedItem {
    string pubDate;
    string title;
    string link;
};

typedef vector<FeedItem> FeedList;

class FeedReader {
    public:
        FeedReader();
        FeedList loadFeed(const string &);
};

#endif // FEEDREADER_H