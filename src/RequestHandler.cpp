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
  if (request.getMethod() == "GET" && request.getPath == "/" &&
      request.getVersion == "HTTP/1.1") {
    request.setStatus(request.getVersion, 200, "OK", OK);
    request.setHeader("Content-Type", "text/html");
    return request.response;
  }
