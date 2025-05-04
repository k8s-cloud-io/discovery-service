#include "WeatherProvider.h"
#include "Credentials.h"

WeatherProvider::WeatherProvider()
:credentials(Credentials::CREDENTIALS_TYPE_NONE) {}


void WeatherProvider::setCredentials(const Credentials &c) {
	credentials = c;
}