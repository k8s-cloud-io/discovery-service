#include "CinnamonDiscovery.h"
#include "Application.h"
#include "FeedLoader.h"
#include "Logger.h"
#include "Timer.h"
#include "User.h"
#include "UserSettings.h"
#include "SqlDatabase.h"
#include "Sqlite3Driver.h"
#include "WeatherProvider.h"

SqlDatabase CinnamonDiscovery::database;

SqlDatabase CinnamonDiscovery::getDatabase() {
    return database;
}

CinnamonDiscovery::CinnamonDiscovery()
:Application(), webService(nullptr) {
    Logger::log("CinnamonDiscovery::CinnamonDiscovery");
}

CinnamonDiscovery::~CinnamonDiscovery() {
    Logger::log("CinnamonDiscovery::~CinnamonDiscovery");
    delete webService;
}

void CinnamonDiscovery::init() {
    UserSettings settings;

    User u = User::current();
    String databasePath = u.getDirectory(XDG_DOCUMENTS_DIR).append("/cinnamon-discovery");
    databasePath = databasePath.append("/discovery.db");

    auto driver = new Sqlite3Driver();
    driver->setDatabaseName(databasePath);
    database.setDriver(driver);

    webService = new CinnamonWebService();
    webService->start();

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