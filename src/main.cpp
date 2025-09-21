/* ============================================================================
 * main.cpp
 *
 * Entry point of the program. This file wires everything together by:
 *   - Creating an HTTPServer instance
 *   - Starting the server to listen for incoming connections
 *   - Continuously serving client requests in a loop
 *   - Stopping the server on shutdown
 *
 * In its current form, the server runs indefinitely until manually terminated
 * (e.g., with Ctrl+C). Each client connection is accepted, processed, and then
 * closed before the server waits for the next one.
 * ============================================================================
 */

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
