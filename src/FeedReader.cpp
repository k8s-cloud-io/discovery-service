#include <libxml/xmlreader.h>
#include "FeedReader.h"
#include "Exception.h"
#include "HttpRequest.h"

FeedReader::FeedReader() {
    LIBXML_TEST_VERSION;
}

FeedList FeedReader::loadFeed(const String &url) {
    FeedList list;

    HttpRequest req(HttpRequest::GET, url);
    auto response = req.exec();

    if(response->getStatusCode() == 200 && response->containsHeader("content-type")) {
        if(String contentType = response->getHeader("content-type");
            contentType.find("application/xml") != String::npos || contentType.find("text/xml") != String::npos ||
            contentType.find("application/rss+xml") != String::npos || contentType.find("text/rss+xml") != String::npos)
        {
            ByteArray buffer = response->getBody();
            buffer.push_back('\0');
            String content((const char *)buffer.data());

            xmlDocPtr doc = xmlReadDoc(reinterpret_cast<const xmlChar *>(content.c_str()), nullptr, nullptr, 0 );
            xmlNode *node = doc->children;
            String version;

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
                    String title, link, pubDate;
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
            throw Exception("Invalid content-type header: " + response->getHeader("content-type"));
        }
    } else {
        throw Exception("unable to read feeds");
    }

    delete response;
    return list;
}