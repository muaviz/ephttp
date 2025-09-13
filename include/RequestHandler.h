#pragma once
#include "HTTPRequest.h"
#include "HTTPResponse.h"

class RequestHandler {
public:
  HTTPResponse handle(const HTTPRequest &request);
};
