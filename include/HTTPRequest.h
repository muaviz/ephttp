#pragma once
#include <string>

class HTTPRequest {
private:
  std::string method;
  std::string path;
  std::string version;

public:
  HTTPRequest(const char *buf);
  std::string getMethod() const;
  std::string getPath() const;
  std::string getVersion() const;

private:
  void parse(const char *buf);
};
