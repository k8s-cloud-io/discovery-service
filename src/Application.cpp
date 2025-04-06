#include "Application.h"
#include <thread>
#include <iostream>

bool Application::running = false;
std::thread Application::mainThread;

void Application::start() {
  Application::running = true;
  Application::mainThread = std::thread([=](){
    while(Application::running) {};
  });
}

Application::~Application() {
  Application::mainThread.join();
  Application::running = false;
}

void Application::quit() {
  Application::running = false;
}