#include "CinnamonDiscovery.h"
#include "FeedLoader.h"
#include "Timer.h"
#include "UserSettings.h"
#include "WeatherLoader.h"

void CinnamonDiscovery::init() {
    UserSettings settings;

    Timer t;
    t.setInterval(1000 * 30);
    t.start([settings](Timer *) {
        FeedLoader::load(settings.getFeeds());
    });

    Timer t2;
    t2.setInterval(1000 * 60 * 30);
    t2.start([](Timer *){
        WeatherLoader::load();
    });
}