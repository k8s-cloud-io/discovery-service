#include <iostream>
#include <thread>
#include "Application.h"

bool Application::running = false;
std::thread Application::mainThread;

int Application::start() {
  Application::running = true;

  atexit([]() {
    std::cout << "atexit!" << std::endl;
    quit();
  });

  std::set_terminate([]() {
    std::cout << "terminate!" << std::endl;
  });

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