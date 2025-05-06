#include <json/json.h>
#include "json/value.h"
#include "weather/WorldWeatherOnlineProvider.h"
#include "CinnamonDiscovery.h"
#include "DateTime.h"
#include "Exception.h"
#include "HttpRequest.h"
#include "Logger.h"
#include "SqlDatabase.h"

#define END_POINT "https://api.worldweatheronline.com/premium/v1/weather.ashx?format=json&fx=yes&fx24=yes&num_of_days=5&date_format=unix&key=%1&q=%2"

void WorldWeatherOnlineProvider::load() const {
    if(credentials.getApiKey().empty()) {
        throw Exception("Exception in class WorldWeatherOnlineProvider: unable to load weather data, missing api key.");
    }

    String s(END_POINT);
    s.arg(2, credentials.getApiKey().c_str(), "Miesbach");

    Url u = Url::parse(s);

    HttpRequest request(HttpRequest::GET, u);
    HttpResponse *response = request.exec();
    String body = response->getBody();
    if(response->getStatusCode() == 200 && body.find("{") == 0) {
        Logger::log(DateTime::currentDateTime().toString() + ": WorldWeatherOnlineProvider - weather was loaded successfully");
        Json::Value root;
        Json::Reader reader;
        reader.parse(body, root);

        if(!root["data"]) {
            Logger::log("WorldWeatherOnlineProvider: unable to load weather, missing data attribute node.");
            return;
        }

        if(root["data"]["weather"]) {
            Json::Value weatherJson = root["data"]["weather"];
            static SqlDatabase db = CinnamonDiscovery::getDatabase();

            for(Json::Value weather: weatherJson) {
                // TODO store to database table(s)
                // Logger::log(weather["date"].asString());
            }
        }
    }
}