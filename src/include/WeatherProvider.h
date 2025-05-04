#ifndef WEATHER_PROVIDER_MANAGER_H
#define WEATHER_PROVIDER_MANAGER_H

#include "Credentials.h"
#include "Location.h"

class WeatherProvider {
	public:

		WeatherProvider() = default;
		virtual ~WeatherProvider() = default;

		void setCredentials(const Credentials &);
		void setLocation(const Location &);
		virtual void load() const = 0;

		Location getLocation() const;

	protected:
		Credentials credentials;
		Location location;
};

#endif // WEATHER_PROVIDER_MANAGER_H