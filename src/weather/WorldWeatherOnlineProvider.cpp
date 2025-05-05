#include "weather/WorldWeatherOnlineProvider.h"
#include "Exception.h"
#include "HttpRequest.h"
#include "Logger.h"

#define END_POINT "https://api.worldweatheronline.com/premium/v1/weather.ashx?format=json&fx=yes&fx24=yes&num_of_days=5&date_format=unix&key=%1&q=%2"

void WorldWeatherOnlineProvider::load() const {
    Logger::log("WorldWeatherOnlineProvider is loading...");
    if(credentials.getApiKey().empty()) {
        throw Exception("Exception in class WorldWeatherOnlineProvider: unable to load weather data, missing api key.");
    }

    String s(END_POINT);
    s.arg(2, credentials.getApiKey().c_str(), "Miesbach");

    Logger::log(s);
    Url u = Url::parse(s);

    HttpRequest request(HttpRequest::GET, u);
    HttpResponse *response = request.exec();
    String body = response->getBody();

    Logger::log(body);
}