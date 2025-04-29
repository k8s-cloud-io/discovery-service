#include <iostream>
#include "WeatherProvider.h"

WeatherProvider::WeatherProvider(ProviderType type)
:type(type), credentials(Credentials::CREDENTIALS_TYPE_NONE) {}

void WeatherProvider::setCredentials(const Credentials &value) {
	credentials = value;
}

void WeatherProvider::load() {
	switch (type) {
		case WEATHER_PROVIDER_WORLD_WEATHER_ONLINE:
		std::cout << "loading weather from world weather online" << std::endl;
		break;

		case WEATHER_PROVIDER_OPEN_WEATHER_MAP:
		std::cout << "loading weather from open weather map" << std::endl;
		break;

		default:
		std::cout << "no weather configured, abort" << std::endl;
		break;
	}
}