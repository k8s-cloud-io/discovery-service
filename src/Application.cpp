#include <thread>
#include "csignal"
#include <cstdlib>
#include "Application.h"
#include <csignal>

bool Application::running = false;
std::thread Application::mainThread;

Application::Application() {
  signal(SIGINT, &Application::quit);
}

int Application::start() {
  Application::running = true;
  mainThread = std::thread([this]() {
    while (Application::running) {}
  });
  return 0;
}

void Application::quit(int signal) {
  Application::running = false;
  if (mainThread.joinable()) {
    mainThread.join();
  }
  std::exit(0);
}