#include "DateTime.h"
#include "String.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

DateTime::DateTime() {
}

DateTime::~DateTime() {}

DateTime DateTime::fromString(const String &date, const String &fmt) {
    DateTime dt;
    std::tm tm = {};
    std::stringstream ss(date);
    ss >> std::get_time(&tm, fmt.c_str());

    dt.tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return dt;
}

int DateTime::getDay() const {
    const std::time_t t_c = std::chrono::system_clock::to_time_t(tp);
    const tm *_tm = std::localtime(&t_c);

    return _tm->tm_mday;
}

int DateTime::getMonth() const {
    const std::time_t t_c = std::chrono::system_clock::to_time_t(tp);
    const tm *_tm = std::localtime(&t_c);

    return _tm->tm_mon;
}

int DateTime::getYear() const {
    const std::time_t t_c = std::chrono::system_clock::to_time_t(tp);
    const tm *_tm = std::localtime(&t_c);

    return _tm->tm_year + 1900;
}

int DateTime::getHour() const {
    const std::time_t t_c = std::chrono::system_clock::to_time_t(tp);
    const tm *_tm = std::localtime(&t_c);

    return _tm->tm_hour;
}

int DateTime::getMinute() const {
    const std::time_t t_c = std::chrono::system_clock::to_time_t(tp);
    const tm *_tm = std::localtime(&t_c);

    return _tm->tm_min;
}

int DateTime::getSecond() const {
    const std::time_t t_c = std::chrono::system_clock::to_time_t(tp);
    const tm *_tm = std::localtime(&t_c);

    return _tm->tm_sec;
}

long DateTime::getMillisecond() const {
    return tp.time_since_epoch().count() / 1000 / 1000 / 1000;
}

void DateTime::addDays(const int value) {
    tp += std::chrono::days(value);
}

void DateTime::addMonths(const int value) {
    tp += std::chrono::months(value);
}

void DateTime::addYears(const int value) {
    tp += std::chrono::years(value);
}

void DateTime::addHours(const int value) {
    tp += std::chrono::hours(value);
}

void DateTime::addMinutes(const int value) {
    tp += std::chrono::minutes(value);
}

void DateTime::addSeconds(const int value) {
    tp += std::chrono::seconds(value);
}

void DateTime::addMilliseconds(const int value) {
    tp += std::chrono::milliseconds(value);
}
