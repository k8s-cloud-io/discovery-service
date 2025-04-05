#include <libxml/xmlreader.h>
#include <iostream>

#include "FeedReader.h"

#include <SqlDatabase.h>
#include <SqlQuery.h>

#include "HttpRequest.h"

using std::cout;
using std::endl;

FeedReader::FeedReader() {
    LIBXML_TEST_VERSION;
}

FeedList FeedReader::loadFeed(const String &url) {
    FeedList list;

    HttpRequest req(HttpRequest::GET, url);
    HttpResponse *response = req.exec();

    if(response->getStatusCode() == 200 && response->containsHeader("content-type")) {
        if(string contentType = response->getHeader("content-type");
            contentType.find("application/xml") != string::npos || contentType.find("text/xml") != string::npos)
        {
            ByteArray buffer = response->getBody();
            buffer.push_back('\0');
            string content(buffer.data());

            xmlDocPtr doc = xmlReadDoc(reinterpret_cast<const xmlChar *>(content.c_str()), nullptr, nullptr, 0 );
            xmlNode *node = doc->children;
            string version;

            while(node) {
                if(xmlStrcmp(node->name, reinterpret_cast<const xmlChar *>("rss")) == 0) {
                    xmlAttr *attributes = node->properties;
                    while(attributes) {
                        if(xmlStrcmp(attributes->name, reinterpret_cast<const xmlChar *>("version")) == 0) {
                            version = reinterpret_cast<char *>(xmlGetProp(node, attributes->name));
                            break;
                        }
                        attributes = attributes->next;
                    }
                    node = node->children;
                } 
                else 
                if(xmlStrcmp(node->name, reinterpret_cast<const xmlChar *>("channel")) == 0) {
                    node = node->children;
                }
                else 
                if(xmlStrcmp(node->name, reinterpret_cast<const xmlChar *>("item")) == 0 && version == "2.0") {
                    xmlNode *itemTags = node->children;
                    string title, link, pubDate;
                    while(itemTags) {
                        if(xmlStrcmp(itemTags->name, reinterpret_cast<const xmlChar *>("title")) == 0) {
                            title = reinterpret_cast<const char *>(itemTags->children->content);
                        }
                        if(xmlStrcmp(itemTags->name, reinterpret_cast<const xmlChar *>("pubDate")) == 0) {
                            pubDate = reinterpret_cast<const char *>(itemTags->children->content);
                        }
                        if(xmlStrcmp(itemTags->name, reinterpret_cast<const xmlChar *>("link")) == 0) {
                            link = reinterpret_cast<const char *>(itemTags->children->content);
                        }
                        itemTags = itemTags->next;
                    }

                    if(!title.empty() && !link.empty() && !pubDate.empty()) {
                        FeedItem feedItem;
                        feedItem.link = link;
                        feedItem.pubDate = pubDate;
                        feedItem.title = title;
                        list.push_back(feedItem);
                    }
                }

                node = node->next;
            }
        } else {
            // throw exception here
            cout << "Invalid content-type: " << response->getHeader("content-type") << endl;
        }
    } else {
        cout << "unable to read feeds" << endl;
    }

    if (!list.empty()) {
        const SqlDatabase db = SqlDatabase::addDatabase(SqlDatabase::TYPE_SQLITE);
        SqlQuery query("CREATE TABLE IF NOT EXISTS feed_item (" \
                "id INTEGER PRIMARY KEY AUTOINCREMENT," \
                "feed TEXT," \
                "title TEXT," \
                "pub_date VARCHAR(255)," \
                "link TEXT," \
                "created_at DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP" \
            ")",
            db
        );
        query.exec();

        query = SqlQuery("DELETE FROM feed_item WHERE feed = ?", db);
        query.bindValue(1, url);
        query.exec();

        query = SqlQuery("INSERT INTO feed_item (feed, title, pub_date, link) VALUES (?, ?, ?, ?)", db);
        for(const auto&[pubDate, title, link]: list) {
            query.clear();
            query.bindValue(1, url);
            query.bindValue(2, title);
            query.bindValue(3, pubDate);
            query.bindValue(4, link);
            query.exec();
        }
    } else {
        cout << "LIST IS EMPTY, NOTHING TO INSERT" << endl;
    }

    delete response;
    return list;
}