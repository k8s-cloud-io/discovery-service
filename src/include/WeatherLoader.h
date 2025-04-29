#ifndef WEATHER_LOADER_H
#define WEATHER_LOADER_H

class WeatherLoader {
    public:
        WeatherLoader();
        virtual ~WeatherLoader();

        static void load();

    private:
        static bool loading;
};

#endif