#pragma once
#include <map>
#include <string>

class HTTPResponse {
private:
  int status;
  std::string message;
  std::map<std::string, std::string> headers;
  std::string body;

public:
  HTTPRespnose(int code, const std::string &msg, const std::string &body);
  void setHeader(const std::string &key, const std::string &value);
  std::string response() const;
};
