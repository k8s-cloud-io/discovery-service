#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H
#include <String.h>

class UnixSocket {
  public:
	explicit UnixSocket(const String &);
    virtual ~UnixSocket();

	void listen();
	void close();

	String getPath() const;
	bool isConnected() const;

  private:
	String path;
	int fd;
};

#endif // UNIX_SOCKET_H