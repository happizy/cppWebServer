#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include "server/controllerLogic.h"


int main() {

    register_controller("/", hello_world);
    register_controller("/index", index);
    register_controller("/asset/default/", get_default_asset);

    // Initialize Winsock
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        std::cerr << "Error initializing Winsock" << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return 1;
    }

    // Bind the socket to an address and port
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);  // Set the port to listen on
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Set the address to listen on any interface
    if (bind(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "Error binding socket" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Start listening for connections
    if (listen(sock, 10) == SOCKET_ERROR) {  // Set the maximum length of the queue of pending connections to 10
        std::cerr << "Error listening for connections" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // The server is now set up and listening for connections
    while (true) {
        // Accept an incoming connection
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        SOCKET client_sock = accept(sock, (sockaddr*)&client_addr, &client_len);
        if (client_sock == INVALID_SOCKET) {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }

        // Write a log message
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        std::cout << "Client connected: " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;

        // Create a new thread to handle the client
        // This allows the server to handle multiple clients at a time
        std::thread client_thread(handle_client, client_sock);
        client_thread.detach();
    }

    // Clean up
    closesocket(sock);
    WSACleanup();

    return 0;
}
