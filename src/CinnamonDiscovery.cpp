#include "CinnamonDiscovery.h"
#include "FeedLoader.h"
#include "Timer.h"
#include "UserSettings.h"
#include <iostream>

void CinnamonDiscovery::init() {
    UserSettings settings;
    
    // initial load before timer starts
    FeedLoader::load(settings.getFeeds());

    Timer t;
    t.setInterval(1000 * 30);
    t.start([settings](Timer *) {
        FeedLoader::load(settings.getFeeds());
    });
}