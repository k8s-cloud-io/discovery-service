#include "CinnamonWebService.h"
#include "File.h"
#include "Logger.h"
#include "UnixSocket.h"
#include "User.h"

UnixSocket *CinnamonWebService::socket = nullptr;

CinnamonWebService::CinnamonWebService() {
    Logger::log("CinnamonWebService::WebService");

    // Initialize the web service
    User u = User::current();
    String runtimeDir = u.getDirectory(XDG_RUNTIME_DIR);
    socketPath = runtimeDir + "/cinnamon-web-service.sock";
    socket = new UnixSocket(socketPath);
}
CinnamonWebService::~CinnamonWebService() {
    Logger::log("CinnamonWebService::~WebService");
}
void CinnamonWebService::start() {
    Logger::log("CinnamonWebService::start");
    socket->listen();
}
void CinnamonWebService::stop() {
    Logger::log("CinnamonWebService::stop");
    if (File::exists(socketPath)) {
        File::remove(socketPath);
    }

    if(socket) {
        delete socket;
        socket = nullptr;
    }
}