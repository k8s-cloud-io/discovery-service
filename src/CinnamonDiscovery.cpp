#include "CinnamonDiscovery.h"
#include "FeedLoader.h"
#include "Timer.h"
#include "UserSettings.h"
#include <iostream>

void CinnamonDiscovery::init() {
    FeedLoader feedLoader;
    UserSettings settings;
    
    Timer t;
    t.setInterval(1000);
    t.start([feedLoader, settings](Timer *) {
        std::cout << "Timer event..." << std::endl;
        feedLoader.load(settings.getFeeds());
    });
}