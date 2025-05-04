#include "WeatherProvider.h"
#include "Credentials.h"
#include "Location.h"

void WeatherProvider::setCredentials(const Credentials &c) {
	credentials = c;
}

void WeatherProvider::setLocation(const Location &loc) {
	location = loc;
}

Location WeatherProvider::getLocation() const {
	return location;
}