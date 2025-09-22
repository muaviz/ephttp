// Copyright (c) 2025 Muaviz
// Licensed under the MIT License. See LICENSE file for details.

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
  void setStatus(const std::string &ver, const int code,
                 const std::string &msg);
  void setBody(const std::string &bdy);
  void setHeader(const std::string &key, const std::string &value);
  std::string response() const;
};
