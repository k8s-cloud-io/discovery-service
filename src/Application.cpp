#include "Application.h"
#include <thread>
#include <iostream>

bool Application::running = false;
std::thread Application::mainThread;

int Application::start() {
  std::set_terminate([]() {
    Application::mainThread.join();
    std::abort();
  });
  Application::running = true;
  Application::mainThread = std::thread([=](){
    while(Application::running) {};
  });
  return 0;
}

Application::~Application() {
  if (mainThread.joinable()) {
    Application::mainThread.join();
    Application::running = false;
  }
}

void Application::quit() {
  Application::running = false;
}