#include "HTTPResponse.h"
#include <sstream>

void HTTPResponse::setStatus(const std::string &ver, const int code,
                             const std::string &msg) {
  version = ver;
  status = code;
  message = msg;
}

void HTTPResponse::setBody(const std::string &bdy) { body = bdy; }

void HTTPResponse ::setHeader(const std::string &key,
                              const std::string &value) {
  headers[key] = value;
}

std::string HTTPResponse ::response() const {
  std::ostringstream res;
  res << version << " " << status << " " << message << "\r\n";
  for (auto &h : headers) {
    res << h.first << ": " << h.second << "\r\n";
  }
  res << "\r\n" << body;
  return res.str();
}
