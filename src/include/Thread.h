#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <list>

class Thread;
typedef std::list<Thread> ThreadList;

class Thread {
  public:
    Thread();
    ~Thread();

    void start();

  private:
    static ThreadList threadList;
    std::thread nativeThread;
};

#endif // THREAD_H