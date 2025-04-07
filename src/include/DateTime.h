#ifndef DATETIME_H
#define DATETIME_H

#include <chrono>
#include "String.h"

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

    static DateTime fromString(const String &, const String &);

  private:
    std::chrono::time_point<std::chrono::system_clock> tp;
};

#endif // DATETIME_H