/* ============================================================================
 * RequestHandler.cpp
 *
 * Implements the RequestHandler class, which decides how to generate HTTP
 * responses for incoming requests. Its role is to act as the "application
 * logic" layer of the server.
 *
 * Responsibilities:
 *   - Inspect the HTTPRequest (method, path, version)
 *   - Decide what content and status code to return
 *   - Build and return an HTTPResponse object
 *
 * Current behavior:
 *   - GET / with HTTP/1.1 → returns a simple static HTML page (200 OK)
 *   - Any other request   → returns a plain text "404 Not Found" response
 *
 * This file can be extended to support more routes, methods, or dynamic
 * responses in the future.
 * ============================================================================
 */

#include "RequestHandler.h"

HTTPResponse RequestHandler ::handle(const HTTPRequest &request) {
  // Example static HTML page for successful GET /
  std::string OK = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Simple Page</title>
</head>
<body>
    <h1>Hello, World!</h1>
    <p>This is a simple HTML response.</p>
</body>
</html>
  )";

  HTTPResponse response;

  // Handle GET request for root path
  if (request.getMethod() == "GET" && request.getPath() == "/" &&
      request.getVersion() == "HTTP/1.1") {
    response.setStatus(request.getVersion(), 200, "OK");
    response.setHeader("Content-Type", "text/html");
    response.setHeader("Connection", "close");
    response.setBody(OK);
  } else {
    // Default case: return 404 Not Found
    response.setStatus(request.getVersion(), 404, "Not Found");
    response.setHeader("Content-Type", "text/plain");
    response.setHeader("Connection", "close");
    response.setBody("404 Not Found");
  }

  return response;
}
