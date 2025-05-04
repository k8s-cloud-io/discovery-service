#include "CinnamonDiscovery.h"
#include "FeedLoader.h"
#include "Timer.h"
#include "UserSettings.h"
#include "WeatherProvider.h"

void CinnamonDiscovery::init() {
    UserSettings settings;
    WeatherProvider *provider = settings.getWeatherProvider();

    Timer t;
    t.setInterval(1000 * 30);
    t.start([settings](Timer *) {
        FeedLoader::load(settings.getFeeds());
    });

    Timer t2;
    t2.setInterval(1000 * 30);
    t2.start([this, provider](Timer *){
         provider->load();
    });
}