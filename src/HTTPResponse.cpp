/* ============================================================================
 * HTTPResponse.cpp
 *
 * Implements the HTTPResponse class, which is responsible for constructing
 * and formatting HTTP responses. A response consists of:
 *   - Status line (HTTP version, status code, and message)
 *   - Headers (e.g., Content-Type, Content-Length)
 *   - Body (e.g., HTML, JSON, plain text)
 *
 * This file provides methods to set these parts and a function to serialize
 * them into a valid HTTP response string for transmission to the client.
 * ============================================================================
 */

#include "HTTPResponse.h"
#include <sstream>

// Set the HTTP version, status code, and status message
void HTTPResponse::setStatus(const std::string &ver, const int code,
                             const std::string &msg) {
  version = ver;
  status = code;
  message = msg;
}

// Set the body of the HTTP response
void HTTPResponse::setBody(const std::string &bdy) { body = bdy; }

// Add or update a header key-value pair in the response
void HTTPResponse ::setHeader(const std::string &key,
                              const std::string &value) {
  headers[key] = value;
}

// Serialize the full HTTP response into a properly formatted string
std::string HTTPResponse ::response() const {
  bool lengthPresent = false;
  std::ostringstream res;

  // Start with the status line
  res << version << " " << status << " " << message << "\r\n";

  // Append headers, tracking if Content-Length is already set
  for (auto &h : headers) {
    if (h.first == "content-length" || h.first == "Content-length" ||
        h.first == "Content-Length") {
      lengthPresent = true;
    }
    res << h.first << ": " << h.second << "\r\n";
  }

  // Add Content-Length header if missing
  if (!lengthPresent) {
    res << "Content-Length: " << body.size() << "\r\n";
  }

  // Blank line separates headers from body
  res << "\r\n" << body;
  return res.str();
}
