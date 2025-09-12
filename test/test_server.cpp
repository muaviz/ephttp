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
  int srv_fd, pr_fd;        // file descriptors for server and peer sockets
  socklen_t peer_addr_size; // peer address size for accept()
  struct sockaddr_in server_addr, peer_addr; // server and peer address structs

  // clearing any garbage value from stucts:
  memset(&server_addr, 0, sizeof(server_addr));
  memset(&peer_addr, 0, sizeof(peer_addr));

  // server address initialisations
  server_addr.sin_family = AF_INET;   // for IPv4
  server_addr.sin_port = htons(8080); // port number 8080
  server_addr.sin_addr.s_addr =
      htonl(INADDR_ANY); // for 0.0.0.0, which means “bind to all interfaces”
  srv_fd =
      socket(AF_INET, SOCK_STREAM, 0); // creating the server socket (TCP/IPv4)

  if (srv_fd == -1)
    handle_error("socket");

  // binding server to 0.0.0.0:8080
  if (bind(srv_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    handle_error("bind");

  // server listen
  if (listen(srv_fd, 1) == -1)
    handle_error("listen");

  peer_addr_size = sizeof(peer_addr);
  // accepting an incoming connection and returning a file descriptor for the
  // peer
  pr_fd = accept(srv_fd, (struct sockaddr *)&peer_addr, &peer_addr_size);
  if (pr_fd == -1)
    handle_error("accept");

  // Reading bytes from peer into buffer
  while (true) {
    char buf[1024];
    long read_bytes = recv(pr_fd, buf, sizeof(buf), 0);
    if (read_bytes == -1)
      handle_error("receiving bytes");
    if (read_bytes == 0) {
      std::cout << "Client Disconnected\n";
      break;
    }
    buf[read_bytes] = '\0';

    // Sending bytes from server to peer
    char imsg[] = "Haha! You said ";
    char fmsg[] = "Didn't you?\n";
    if (send(pr_fd, imsg, strlen(imsg), 0) == -1)
      handle_error("sending initial bytes");
    if (send(pr_fd, buf, strlen(buf), 0) == -1)
      handle_error("sending bytes");
    if (send(pr_fd, fmsg, strlen(fmsg), 0) == -1)
      handle_error("sending final bytes");
  }
  // Closing server and peer sockets
  if (close(srv_fd) == -1)
    handle_error("close server");
  if (close(pr_fd) == -1)
    handle_error("close peer");
  return 0;
}
