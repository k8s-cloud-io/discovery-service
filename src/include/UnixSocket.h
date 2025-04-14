#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H
#include <String.h>
#include <thread>
#include <list>

class SocketEvent {
	public:
		SocketEvent() = default;
};

class SocketEventListener {
	public:
		SocketEventListener() = default;
		virtual ~SocketEventListener() = default;

		virtual void onSocketEvent(SocketEvent *);
};

typedef std::list<SocketEventListener> SocketEventListeners;

class UnixSocket {
  public:
	explicit UnixSocket(const String &);
    virtual ~UnixSocket();

	void listen();
	void close();
	void addEventListener(const SocketEventListener &);

	String getPath() const;
	bool isListening() const;

  private:
	bool listening;
	String path;
	int fd;
	std::thread runner;
	SocketEventListeners listeners;
};

#endif // UNIX_SOCKET_H