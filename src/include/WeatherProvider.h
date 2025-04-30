#ifndef WEATHER_PROVIDER_MANAGER_H
#define WEATHER_PROVIDER_MANAGER_H

#include "Credentials.h"

class WeatherProvider {
	public:
		enum ProviderType {
		WEATHER_PROVIDER_NONE = 0,
		WEATHER_PROVIDER_OPEN_WEATHER_MAP,
		WEATHER_PROVIDER_WORLD_WEATHER_ONLINE
		};

		WeatherProvider(ProviderType type = WEATHER_PROVIDER_NONE);
		virtual ~WeatherProvider() = default;

		void setCredentials(const Credentials &);
		void load();

	private:
		ProviderType type;
		Credentials credentials;
};

#endif // WEATHER_PROVIDER_MANAGER_H