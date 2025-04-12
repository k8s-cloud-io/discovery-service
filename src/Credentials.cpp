#include "Credentials.h"

Credentials::Credentials(CredentialsType type)
:type(type) {}

void Credentials::setUserName(const String &value) {
  userName = value;
}

void Credentials::setPassword(const String &value) {
  password = value;
}

void Credentials::setApiKey(const String &value) {
  apiKey = value;
}

String Credentials::getUserName() const {
  return userName;
}

String Credentials::getPassword() const {
  return password;
}

String Credentials::getApiKey() const {
  return apiKey;
}