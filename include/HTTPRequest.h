// Copyright (c) 2025 Muaviz
// Licensed under the MIT License. See LICENSE file for details.

#pragma once
#include <map>
#include <string>

class HTTPRequest {
private:
  std::string method;
  std::string path;
  std::string version;
  std::map<std::string, std::string> headers;

public:
  HTTPRequest(const char *buf);
  std::string getMethod() const;
  std::string getPath() const;
  std::string getVersion() const;

private:
  void parse(const char *buf);
};
