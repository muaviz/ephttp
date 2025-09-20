#include "HTTPServer.h"

int main(void) {
  HTTPServer server;
  server.start();
  while (true) {
    server.serve();
  }
  server.stop();
  return 0;
}
