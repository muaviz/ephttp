/* ============================================================================
 * HTTPRequest.cpp
 *
 * This file implements the HTTPRequest class, which is responsible for parsing
 * raw HTTP request data received from a client. It extracts and stores:
 *   - The HTTP method (e.g., GET, POST)
 *   - The request path (e.g., /, /index.html)
 *   - The HTTP version (e.g., HTTP/1.1)
 *   - Any request headers (e.g., Host, User-Agent)
 *
 * These values can then be accessed via getter methods and are typically used
 * by `RequestHandler.cpp` to generate the correct HTTP response.
 * ============================================================================
 */

#include "HTTPRequest.h"
#include <iostream>
#include <sstream>
#include <string>

HTTPRequest ::HTTPRequest(const char *buf) { parse(buf); }

// Getters for request attributes
std::string HTTPRequest::getMethod() const { return method; }
std::string HTTPRequest::getPath() const { return path; }
std::string HTTPRequest::getVersion() const { return version; }

// Parses the raw request buffer into method, path, version, and headers
void HTTPRequest::parse(const char *buf) {
  std::istringstream stream(buf);

  // First line contains: METHOD PATH VERSION
  std::string firstLine;
  std::getline(stream, firstLine); // first line: method, path, version

  // Parse headers line by line until an empty line (CRLF) is reached
  std::string nxt;
  while (std::getline(stream, nxt)) {
    if (nxt.empty())
      break;
    std::istringstream nxtstream(nxt);
    std::string key, value;

    if (std::getline(nxtstream, key, ':') && std::getline(nxtstream, value)) {
      value.erase(0, value.find_first_not_of(" ")); // trim leading spaces
      headers[key] = value;
    }
  }

  // Extract method, path, version from the request line
  std::istringstream iss(firstLine);
  iss >> method >> path >> version;

  // Remove trailing carriage return if present (from CRLF line endings)
  if (!version.empty() && version.back() == '\r') {
    version.pop_back();
  }
}
