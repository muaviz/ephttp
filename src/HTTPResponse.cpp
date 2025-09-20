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
  bool lengthPresent = false;
  std::ostringstream res;
  res << version << " " << status << " " << message << "\r\n";
  for (auto &h : headers) {
    if (h.first == "content-length" || h.first == "Content-length" ||
        h.first == "Content-Length") {
      lengthPresent = true;
    }
    res << h.first << ": " << h.second << "\r\n";
  }
  if (!lengthPresent) {
    res << "Content-Length: " << body.size() << "\r\n";
  }
  res << "\r\n" << body;
  return res.str();
}
