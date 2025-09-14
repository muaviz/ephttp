#include "HTTPServer.h"

int main(void) {
  HTTPServer server;
  server.start();
  server.read();
  server.stop();
  return 0;
}
