#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include "String.h"

class Credentials {
  public:
    enum CredentialsType {
      CREDENTIALS_TYPE_NONE = 0,
      CREDENTIALS_TYPE_API_KEY,
      CREDENTIALS_TYPE_USER,
    };

    Credentials(CredentialsType);

    void setUserName(const String &);
    void setPassword(const String &);
    void setApiKey(const String &);

    String getUserName() const;
    String getPassword() const;
    String getApiKey() const;

  private:
    CredentialsType type;
    String userName;
    String password;
    String apiKey;
};

#endif // CREDENTIALS_H