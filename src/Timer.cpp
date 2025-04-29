#include <thread>
#include "Timer.h"

Timer::Timer()
:interval(0),running(false) {}

Timer::~Timer() {
  timer.join();
  stop();
}

int Timer::getInterval() const {
  return interval;
}

void Timer::setInterval(int i) {
  interval = i;
}

void Timer::start(const std::function<void(Timer *)> &cb) {
  running = true;
  std::thread t([this, cb](){
    (cb)(this);
  });
  t.detach();
  
  timer = std::thread([this, cb]() {
      do {
          std::this_thread::sleep_for(std::chrono::milliseconds(interval));
          std::thread t([this, cb](){
            (cb)(this);
          });
          t.detach();
      } while(running);
  });
}

void Timer::stop() {
  running = false;
}