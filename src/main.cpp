#include "HTTPServer.h"

int main(void) {
  HTTPServer server;
  while (true) {
    server.start();
    server.read();
    server.stop();
  }
  return 0;
}
