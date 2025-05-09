#ifndef APPLICATION_H
#define APPLICATION_H

#include <thread>

class Application {
  public:
    Application();
    virtual ~Application() = default;

    int start();
    static void quit(int signal = 0);

    private:
      static bool running;
      static std::thread mainThread;
};

#endif // APPLICATION_H