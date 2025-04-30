#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <thread>
using std::thread;

class Timer {
    public:
      Timer();
      virtual ~Timer();

      int getInterval() const;

      void setInterval(int);

      void start(const std::function<void(Timer *)> &);
      void stop();

    private:
      int interval;
      bool running;
      thread timer;
};

#endif //TIMER_H
