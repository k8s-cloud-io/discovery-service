#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include "String.h"

class Credentials {
  public:

    Credentials() = default;
    virtual ~Credentials() = default;

    void setUserName(const String &);
    void setPassword(const String &);
    void setApiKey(const String &);

    String getUserName() const;
    String getPassword() const;
    String getApiKey() const;

  private:
    String userName;
    String password;
    String apiKey;
};

#endif // CREDENTIALS_H