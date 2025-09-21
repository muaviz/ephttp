/* ============================================================================
 * HTTPServer.cpp
 *
 * Implements the HTTPServer class, which manages the core server-side logic
 * for handling HTTP over TCP. Its responsibilities include:
 *   - Creating and binding a TCP socket to a given port
 *   - Listening for incoming client connections
 *   - Accepting connections and reading raw HTTP requests
 *   - Passing requests to the RequestHandler to generate responses
 *   - Sending responses back to clients
 *
 * This class abstracts away the low-level socket operations and provides a
 * simple interface for starting, serving, and stopping the HTTP server.
 * ============================================================================
 */

#include "HTTPServer.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "RequestHandler.h"

// C headers for networking
#include <arpa/inet.h>  // htons, htonl, inet_addr
#include <cstring>      // memset
#include <iostream>     // std::cout, perror
#include <netinet/in.h> // sockaddr_in
#include <sys/socket.h> // socket, bind, listen, accept
#include <unistd.h>     // close

// Constructor: initializes server socket, binds to the given port
HTTPServer ::HTTPServer(int port) : port(port) {
  peer_fd = -1;
  memset(&server_addr, 0, sizeof(server_addr));
  memset(&peer_addr, 0, sizeof(peer_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1)
    handle_error("socket");
  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1)
    handle_error("bind");
}

// Start listening for incoming client connections
void HTTPServer ::start() {
  if (listen(server_fd, 1) == -1)
    handle_error("listen");
}

// Accepts a client connection, reads request, delegates to handler, and replies
void HTTPServer ::serve() {
  peer_addr_size = sizeof(peer_addr);
  peer_fd = accept(server_fd, (struct sockaddr *)&peer_addr, &peer_addr_size);
  if (peer_fd == -1)
    handle_error("accept");

  // Read raw HTTP request from client
  char buf[1024];
  long read_bytes = recv(peer_fd, buf, sizeof(buf), 0);
  if (read_bytes == -1)
    close(peer_fd);
  if (read_bytes == 0) {
    std::cout << "Client Disconnected\n";
  }
  buf[read_bytes] = '\0';

  // Parse request and generate response
  HTTPRequest request(buf);
  RequestHandler handler;
  HTTPResponse response = handler.handle(request);

  // Send response back to client
  std::string respStr = response.response();
  send(peer_fd, respStr.c_str(), respStr.size(), 0);

  // Close the client connection
  close(peer_fd);
}

// Stop the server by closing the server socket
void HTTPServer::stop() {
  if (close(server_fd) == -1)
    handle_error("close server");
}

// Destructor: ensures the server is stopped properly
HTTPServer ::~HTTPServer() { stop(); }
