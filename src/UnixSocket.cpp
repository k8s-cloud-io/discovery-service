#include "UnixSocket.h"

#include <Dir.h>
#include <File.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <thread>

UnixSocket::UnixSocket(const String &path)
	:listening(false), path(path), fd(-1) {
}

UnixSocket::~UnixSocket() {
	runner.join();
	close();
}

void UnixSocket::listen() {
	if (fd > -1) {
		std::cout << "error in UnixSocket: unable to listen (socket in use)" << std::endl;
		exit(1);
	}

	File f(path);
	if (const String dir = f.getDirectory(); !File::isDirectory(dir)) {
		std::cout << "error in UnixSocket: directory " << dir << " does not exists" << std::endl;
		exit(1);
	}

	sockaddr_un address;
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, path.c_str());
	fd = socket(AF_UNIX, SOCK_STREAM, 0);

	if (fd == -1) {
		std::cout << "error in UnixSocket: unable to create socket" << std::endl;
		exit(1);
	}

	if (bind(fd, reinterpret_cast<sockaddr *>(&address), sizeof(address)) != 0) {
		std::cout << "error in UnixSocket: unable to bind socket" << std::endl;
		exit(1);
	}

	if (::listen(fd, 100) != 0) {
		std::cout << "error in UnixSocket: unable to listen on socket" << std::endl;
		exit(1);
	}

	listening = true;
	runner = std::thread([this]() {
		while (isListening()) {
			// TODO implement IO: without, the service is stopping
			sleep(1);
			std::cout << "Listening..." << std::endl;
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