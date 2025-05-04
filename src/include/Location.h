#ifndef LOCATION_H
#define LOCATION_H

#include "String.h"

class Location {
    public:
        Location() = default;
        virtual ~Location() = default;

        void setCity(const String &);
        void setState(const String &);
        void setCountry(const String &);
        void setLatitude(const String &);
        void setLongitude(const String &);

    private:
        String city;
        String state;
        String country;
        String latitude;
        String longitude;
};

#endif // LOCATION_H