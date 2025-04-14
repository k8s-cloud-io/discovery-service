#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H
#include <String.h>
#include <thread>

class UnixSocket {
  public:
	explicit UnixSocket(const String &);
    virtual ~UnixSocket();

	void listen();
	void close();

	String getPath() const;
	bool isListening() const;

  private:
	bool listening;
	String path;
	int fd;
	std::thread runner;
};

#endif // UNIX_SOCKET_H