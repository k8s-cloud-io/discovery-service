#ifndef WEATHER_PROVIDER_H
#define WEATHER_PROVIDER_H

#include "Credentials.h"

class WeatherProvider {
  public:
	enum ProviderType {
	  PROVIDER_NONE = 0,
	  PROVIDER_OPEN_WEATHER_MAP,
	  PROVIDER_WORLD_WEATHER_ONLINE
	};

	explicit WeatherProvider(ProviderType = PROVIDER_NONE);

    void setCredentials(const Credentials &);

	ProviderType getProviderType() const;
    Credentials getCredentials() const;

  private:
	ProviderType type;
    Credentials credentials;
};

#endif // WEATHER_PROVIDER_H