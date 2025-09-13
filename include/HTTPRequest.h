#pragma once
#include <string>

class HTTPRequest {
private:
  std::string method;
  std::string path;
  std::string version;

public:
  HTTPRequest(const char *buf);
  std::string getMethod();
  std::string getPath();
  std::string getVersion();

private:
  void parse(const char *buf);
};
