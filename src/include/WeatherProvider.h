#ifndef WEATHER_PROVIDER_MANAGER_H
#define WEATHER_PROVIDER_MANAGER_H

#include "Credentials.h"

class WeatherProvider {
	public:

		WeatherProvider();
		virtual ~WeatherProvider() = default;

		void setCredentials(const Credentials &);
		virtual void load() const = 0;

	protected:
		Credentials credentials;
};

#endif // WEATHER_PROVIDER_MANAGER_H