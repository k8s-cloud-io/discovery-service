#include <iostream>
#include "Exception.h"
#include "UserSettings.h"
#include "WeatherLoader.h"

bool WeatherLoader::loading = false;

WeatherLoader::WeatherLoader(){}
WeatherLoader::~WeatherLoader(){}

void WeatherLoader::load() {
    if(loading) {
        return;
    }

    loading = true;
    try {
        std::cout << "WeatherLoader: loading weather..." << std::endl;
        UserSettings settings;
        WeatherProvider provider = settings.getWeatherProvider();
        provider.load();
        loading = false;
    }
    catch(const Exception &e) {
        loading = false;
        throw Exception(e);
    }
}