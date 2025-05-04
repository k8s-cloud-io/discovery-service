#include "weather/WorldWeatherOnlineProvider.h"
#include "Exception.h"
#include "HttpRequest.h"
#include "Logger.h"

#define END_POINT "https://api.worldweatheronline.com/premium/v1/weather.ashx?format=json"

void WorldWeatherOnlineProvider::load() const {
    Logger::log("WorldWeatherOnlineProvider is loading...");
    if(credentials.getApiKey().empty()) {
        throw Exception("Exception in class WorldWeatherOnlineProvider: unable to load weather data, missing api key.");
    }

    HttpRequest request(HttpRequest::GET, END_POINT);
    HttpResponse *response = request.exec();
    String body = response->getBody();

    Logger::log(body);
}