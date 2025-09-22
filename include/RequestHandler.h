// Copyright (c) 2025 Muaviz
// Licensed under the MIT License. See LICENSE file for details.

#pragma once
#include "HTTPRequest.h"
#include "HTTPResponse.h"

class RequestHandler {

public:
  HTTPResponse handle(const HTTPRequest &request);
};
