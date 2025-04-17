#ifndef DATETIME_H
#define DATETIME_H

#include <chrono>
#include "String.h"
using std::chrono::time_point;
using std::chrono::system_clock;


class DateTime final {
  public:
    DateTime();
    ~DateTime();

    void addDays(int);
    void addHours(int);
    void addMinutes(int);
    void addSeconds(int);
    void addMilliseconds(int);
    void addYears(int);
    void addMonths(int);

    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    long getMillisecond() const;
    String toString(const String &fmt = String()) const;

    static DateTime fromString(const String &, const String &);

  private:
    time_point<system_clock> tp;
};

#endif // DATETIME_H