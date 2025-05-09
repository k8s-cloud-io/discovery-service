#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "File.h"
#include "Logger.h"
#include "UnixSocket.h"

UnixSocket::UnixSocket(const String &path)
	:listening(false), path(path), fd(-1) {
		listeners = new SocketEventListeners();
}

UnixSocket::~UnixSocket() {
	runner.join();
	close();
}

void UnixSocket::listen() {
	if (fd > -1) {
		Logger::log("error in UnixSocket: unable to listen (socket in use)");
		exit(1);
	}

	File f(path);
	if (const String dir = f.getDirectory(); !File::isDirectory(dir)) {
		Logger::log("error in UnixSocket: directory " + dir + " does not exists");
		exit(1);
	}

	if(File::exists(path)) {
		unlink(path.c_str());
	}

	sockaddr_un address;
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, path.c_str());
	fd = socket(AF_UNIX, SOCK_STREAM, 0);

	if (fd == -1) {
		Logger::log("error in UnixSocket: unable to create socket");
		exit(1);
	}

	if (bind(fd, reinterpret_cast<sockaddr *>(&address), sizeof(address)) != 0) {
		Logger::log("error in UnixSocket: unable to bind socket");
		exit(1);
	}

	if (::listen(fd, 100) != 0) {
		Logger::log("error in UnixSocket: unable to listen on socket");
		exit(1);
	}

	listening = true;
	runner = std::thread([this, address]() {
		Logger::log("UnixSocket::listen: listening for unix domain socket events on " + path);

		while (isListening()) {
			socklen_t len = sizeof(address);
			int s = accept(fd, (sockaddr *)&address, &len);
			if(s != 0) {
				std::thread child([this,s](){
					Logger::log(String("connection received, calling ") + String::valueOf(listeners->size()) + " listeners.");
					for(auto it = listeners->begin(); it != listeners->end(); ++it) {
						SocketEvent *e = new SocketEvent();
						e->socket = s;
						SocketEventListener *l = *it;
						l->onSocketEvent(e);
						Logger::log("called listener...");
					}
				});
				child.detach();
			}
		}
	});
}

void UnixSocket::close() {
	listening = false;
	if (fd > -1) {
		::close(fd);
		fd = -1;
	}
	if (File::exists(path)) {
		unlink(path.c_str());
	}
}

String UnixSocket::getPath() const {
	return path;
}

bool UnixSocket::isListening() const {
	return listening;
}

void UnixSocket::addEventListener(SocketEventListener *l) {
	listeners->push_back(l);
}