#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <functional>
#include <thread>

class Timer {
    public:
      Timer();
      ~Timer();

      int getInterval() const;

      void setInterval(int);

      void start(const std::function<void(Timer *)> &);
      void stop();

    private:
      int interval;
      bool running;
      std::thread timer;
};

#endif //TIMER_H
