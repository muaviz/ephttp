#pragma once
#include <map>
#include <string>

class HTTPResponse {
private:
  std::string version;
  int status;
  std::string message;
  std::map<std::string, std::string> headers;
  std::string body;

public:
  void setStatus(const std::string &version, const int status,
                 const std::string &message, std::string &body);
  void setHeader(const std::string &key, const std::string &value);
  std::string response() const;
};
