#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H

#include <winsock2.h>
#include <sstream>
#include <functional>

#include "routingLogic.h" // Include routingLogic.h here

void register_controller(const std::string& resource, std::function<std::pair<Doctype, std::string>(const std::string&)> controller);
void handle_client(SOCKET client_sock);

#endif
