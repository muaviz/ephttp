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

  std::string nxt;
  while (std::getline(stream, nxt)) {
    if (nxt.empty()) {
      std::istringstream nxtstream(nxt);
      std::string key, value;

      if (std::getline(nxtstream, key, ':') && std::getline(nxtstream, value)) {
        value.erase(0, value.find_first_not_of(" "));
        headers[key] = value;
      }
    }
  }

  std::istringstream iss(firstLine);
  iss >> method >> path >> version;
  if (!version.empty() && version.back() == '\r') {
    version.pop_back();
  }
}
