#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <list>
using std::thread;

class Thread;
typedef std::list<Thread> ThreadList;

class Thread {
  public:
    Thread();
    ~Thread();

    void start();

  private:
    static ThreadList threadList;
    thread nativeThread;
};

#endif // THREAD_H