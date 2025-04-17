#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H

#include <thread>
#include <list>
#include "String.h"
using std::list;
using std::thread;

class UnixSocket;

class SocketEvent {
	public:
		SocketEvent();

		int getSocket() const;

	private:
		friend UnixSocket;
		int socket;
};

inline
SocketEvent::SocketEvent()
:socket(-1) {}

inline
int SocketEvent::getSocket() const {
	return socket;
}

class SocketEventListener {
	public:
		SocketEventListener() = default;
		virtual ~SocketEventListener() = default;

		virtual void onSocketEvent(SocketEvent *);
};

inline
void SocketEventListener::onSocketEvent(SocketEvent *) {}

typedef list<SocketEventListener *> SocketEventListeners;

class UnixSocket {
  public:
	explicit UnixSocket(const String &);
    virtual ~UnixSocket();

	void listen();
	void close();
	void addEventListener(SocketEventListener *);

	String getPath() const;
	bool isListening() const;

  private:
	bool listening;
	String path;
	int fd;
	thread runner;
	SocketEventListeners *listeners;
};

#endif // UNIX_SOCKET_H