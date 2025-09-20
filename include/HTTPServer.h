#pragma once

#include <cstdio>       // For perror
#include <cstdlib>      // For exit
#include <netinet/in.h> // For sockaddr_in
#include <unistd.h>     // For close

#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

class HTTPServer {
private:
  int server_fd, peer_fd;
  int port;
  socklen_t peer_addr_size;
  struct sockaddr_in server_addr, peer_addr;

public:
  HTTPServer(int port = 8080);
  ~HTTPServer();
  void start();
  void serve();
  void stop();
};
