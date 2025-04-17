#ifndef APPLICATION_H
#define APPLICATION_H

#include <thread>

class Application final {
  public:
    Application() = default;
    ~Application();

    int start();
    static void quit();

    private:
      static bool running;
      static std::thread mainThread;
};

#endif // APPLICATION_H