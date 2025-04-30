#include <thread>
#include "Application.h"

bool Application::running = false;
std::thread Application::mainThread;

int Application::start() {
  Application::running = true;

  mainThread = std::thread([&]() {
    while (running) {};
  });
  return 0;
}

Application::~Application() {
  mainThread.join();
  quit();
}

void Application::quit() {
  Application::running = false;
}