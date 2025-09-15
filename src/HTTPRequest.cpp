#include "HTTPRequest.h"
#include <iostream>
#include <sstream>
#include <string>

HTTPRequest ::HTTPRequest(const char *buf) { parse(buf); }

std::string HTTPRequest::getMethod() const { return method; }

std::string HTTPRequest::getPath() const { return path; }

std::string HTTPRequest::getVersion() const { return version; }

void HTTPRequest::parse(const char *buf) {
  std::istringstream stream(buf);
  std::string firstLine;
  std::getline(stream, firstLine);
  std::istringstream iss(firstLine);
  iss >> method >> path >> version;
  if (!version.empty() && version.back() == '\r') {
    version.pop_back();
  }
}
