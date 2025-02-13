#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <regex>
#include <filesystem>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <functional>

// Assuming Doctype is an enum defined somewhere in clientHandle.h
enum Doctype { TEXT, HTML, JSON, PNG, GIF, WEBP, CSS };

std::unordered_map<std::string, std::function<std::pair<Doctype, std::string>(const std::string&)>> controllers;

void register_controller(const std::string& resource, std::function<std::pair<Doctype, std::string>(const std::string&)> controller) {
    controllers[resource] = controller;
}

std::pair<std::string, std::string> splitPathAndFileName(const std::string& fullPath) {
    size_t found = fullPath.find_last_of("/\\"); // Find last occurrence of path separator
    if (found != std::string::npos) {
        std::string path = fullPath.substr(0, found + 1); // Extract substring before the last occurrence
        std::string fileName = fullPath.substr(found + 1); // Extract substring after the last occurrence
        return std::make_pair(path, fileName);
    }
    return std::make_pair("", fullPath); // Return fullPath as filename if no path separator found
}

std::string get_response(char buf[]) {
    std::cmatch request_match;

    std::regex request_regex("^GET (/[^ ]*) HTTP/[^ ]*\\r\\n", std::regex::multiline);
    if (!std::regex_search(buf, request_match, request_regex)) {
        return "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
    }

    std::string controllerMatch = request_match[1];
    std::string resource;

    std::map<Doctype, std::string> response_types = {
        {TEXT, "text/plain"},
        {HTML, "text/html"},
        {JSON, "text/json"},
        {PNG, "image/*"},
        {GIF, "image/*"},
        {WEBP, "image/webp"},
        {CSS, "text/css"}
    };

    // asset requests management
    std::regex asset_regex("/asset/*", std::regex::multiline);
    if (std::regex_search(controllerMatch.c_str(), request_match, asset_regex)) {
        std::pair<std::string, std::string> pathAndFileName = splitPathAndFileName(controllerMatch);
        controllerMatch = pathAndFileName.first;
        resource = pathAndFileName.second;
    }

    auto iterator = controllers.find(controllerMatch);

    if (iterator == controllers.end() || iterator->second(resource).second.empty()) {
        return "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
    }

    Doctype doctype = iterator->second(resource).first;
    std::string response_body = iterator->second(resource).second;

    std::stringstream response;
    response << "HTTP/1.1 200 OK\r\n"
             << "Content-Type: " + response_types[doctype] + "\r\n"
             << "Content-Length: " << response_body.size() << "\r\n"
             << "\r\n"
             << response_body;

    return response.str();
}

// client handling method
void handle_client(int client_sock) {
    char request_buf[1024];
    int request_len = recv(client_sock, request_buf, sizeof(request_buf), 0);
    if (request_len <= 0) {
        // Error or connection closed by client
        close(client_sock);
        return;
    }

    // end request string
    request_buf[request_len] = '\0';

    std::string response = get_response(request_buf);

    // Send the response to the client
    send(client_sock, response.c_str(), response.size(), 0);

    // Shutdown the socket to signal that we're done sending data
    shutdown(client_sock, SHUT_WR);

    // Close the client socket
    close(client_sock);
}
