#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int main(void) {
  int srv_fd, pr_fd;
  socklen_t peer_addr_size;
  struct sockaddr_in server_addr, peer_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  memset(&peer_addr, 0, sizeof(peer_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  srv_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (srv_fd == -1)
    handle_error("socket");
  if (bind(srv_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    handle_error("bind");
  if (listen(srv_fd, 1) == -1)
    handle_error("listen");

  peer_addr_size = sizeof(peer_addr);
  pr_fd = accept(srv_fd, (struct sockaddr *)&peer_addr, &peer_addr_size);
  if (pr_fd == -1)
    handle_error("accept");

  char buf[1024];
  long read_bytes = recv(pr_fd, buf, sizeof(buf), 0);
  if (read_bytes == -1)
    handle_error("receiving bytes");
  buf[read_bytes] = '\0';

  char msg[] = "Hello TCP\n";
  if (send(pr_fd, msg, strlen(msg), 0) == -1)
    handle_error("sending bytes");

  if (close(srv_fd) == -1)
    handle_error("close server");
  if (close(pr_fd) == -1)
    handle_error("close peer");
  return 0;
}
