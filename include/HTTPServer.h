#pragma once

class HTTPServer {
private:
  int server_fd, peer_fd;
  int port;
  socklen_t peer_addr_size;
  struct sockaddr_in server_addr, peer_addr;

public:
  HTTPServer(int port);
  ~HTTPServer();
  void start();
  char *read();
  void stop();
};
