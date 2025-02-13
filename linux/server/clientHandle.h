#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include <functional>
#include <cstring> // For memset and other C-string functions
#include "routingLogic.h" // Include routingLogic.h here

// Function to register a controller
void register_controller(const std::string& resource, std::function<std::pair<Doctype, std::string>(const std::string&)> controller);

// Function to handle a client connection
void handle_client(int client_sock); // Use 'int' instead of 'SOCKET' for Linux

#endif