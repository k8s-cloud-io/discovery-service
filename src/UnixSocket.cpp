#include "UnixSocket.h"

#include <Dir.h>
#include <File.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

UnixSocket::UnixSocket(const String &path)
	:path(path), fd(-1) {
}

UnixSocket::~UnixSocket() {
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
		fd = -1;
		exit(1);
	}

	if (::listen(fd, 100) != 0) {
		std::cout << "error in UnixSocket: unable to listen on socket" << std::endl;
		fd = -1;
		exit(1);
	}
}

void UnixSocket::close() {
	if (fd > -1) {
		::close(fd);
		fd = -1;
		unlink(path.c_str());
		std::cout << "unix socket closed" << std::endl;
	}
}

String UnixSocket::getPath() const {
	return path;
}

bool UnixSocket::isConnected() const {
	return fd > -1;
}