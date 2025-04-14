#include "Thread.h"

ThreadList Thread::threadList;

Thread::Thread() {

}

Thread::~Thread() {

}

void Thread::start() {
  // nativeThread = std::thread(&Thread::run, this);
}