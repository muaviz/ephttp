#include "RequestHandler.h"

HTTPResponse RequestHandler ::handle(const HTTPRequest &request) {
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

  if (request.getMethod() == "GET" && request.getPath() == "/" &&
      request.getVersion() == "HTTP/1.1") {
    response.setStatus(request.getVersion(), 200, "OK");
    response.setHeader("Content-Type", "text/html");
    response.setBody(OK);
  } else {
    response.setStatus(request.getVersion(), 404, "Not Found");
    response.setHeader("Content-Type", "text/plain");
    response.setBody("404 Not Found");
  }

  return response;
}
