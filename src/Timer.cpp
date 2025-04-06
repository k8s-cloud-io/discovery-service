#include "Timer.h"
#include <thread>

Timer::Timer()
:interval(0),running(false) {}

Timer::~Timer() {
  timer.join();
  running = false;
}

int Timer::getInterval() const {
  return interval;
}

void Timer::setInterval(int i) {
  interval = i;
}

void Timer::start(const std::function<void(Timer *)> &cb) {
  running = true;
  timer = std::thread([this, cb]() {
      do {
          std::this_thread::sleep_for(std::chrono::milliseconds(interval));
          (cb)(this);
      } while(running);
  });
}

void Timer::stop() {
  running = false;
}