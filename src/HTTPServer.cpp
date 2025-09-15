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

HTTPServer ::HTTPServer(int port) : port(port) {
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

void HTTPServer ::start() {
  if (listen(server_fd, 1) == -1)
    handle_error("listen");

  peer_addr_size = sizeof(peer_addr);

  peer_fd = accept(server_fd, (struct sockaddr *)&peer_addr, &peer_addr_size);
  if (peer_fd == -1)
    handle_error("accept");
}

void HTTPServer ::read() {
  // Reading bytes from peer into buffer
  while (true) {
    char buf[1024];
    long read_bytes = recv(peer_fd, buf, sizeof(buf), 0);
    if (read_bytes == -1)
      handle_error("receiving bytes");
    if (read_bytes == 0) {
      std::cout << "Client Disconnected\n";
      break;
    }
    buf[read_bytes] = '\0';

    HTTPRequest request(buf);
    RequestHandler handler;
    HTTPResponse response = handler.handle(request);

    // Sending bytes from server to peer
    std::string respStr = response.response();
    if (send(peer_fd, respStr.c_str(), respStr.size(), 0) == -1)
      handle_error("sending bytes");
    stop();
  }
}

void HTTPServer::stop() {
  // Closing server and peer sockets
  if (close(server_fd) == -1)
    handle_error("close server");
  if (close(peer_fd) == -1)
    handle_error("close peer");
}

HTTPServer ::~HTTPServer() { stop(); }
