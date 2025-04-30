#include "Logger.h"
#include "WeatherProvider.h"

WeatherProvider::WeatherProvider(ProviderType type)
:type(type), credentials(Credentials::CREDENTIALS_TYPE_NONE) {}

void WeatherProvider::setCredentials(const Credentials &value) {
	credentials = value;
}

void WeatherProvider::load() {
	switch (type) {
		case WEATHER_PROVIDER_WORLD_WEATHER_ONLINE:
		Logger::log("loading weather from world weather online");
		break;

		case WEATHER_PROVIDER_OPEN_WEATHER_MAP:
		Logger::log("loading weather from open weather map");
		break;

		default:
		Logger::log("no weather configured, abort");
		break;
	}
}