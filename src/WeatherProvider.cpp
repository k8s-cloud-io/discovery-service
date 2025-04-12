#include "WeatherProvider.h"

WeatherProvider::WeatherProvider(ProviderType type)
:type(type), credentials(Credentials::CREDENTIALS_TYPE_NONE) {}

WeatherProvider::ProviderType WeatherProvider::getProviderType() const {
  return type;
}

void WeatherProvider::setCredentials(const Credentials &value) {
  credentials = value;
}

Credentials WeatherProvider::getCredentials() const {
  return credentials;
}