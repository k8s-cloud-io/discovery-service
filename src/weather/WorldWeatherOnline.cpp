#include "weather/WorldWeatherOnline.h"
#include "Credentials.h"

WorldWeatherOnline::WorldWeatherOnline()
:credentials(Credentials::CREDENTIALS_TYPE_NONE) {}

void WorldWeatherOnline::setCredentials(const Credentials &creds) {
    credentials = creds;
}