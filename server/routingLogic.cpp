#include "routingLogic.h"
#include <iostream>
#include <chrono>

std::string read_file(const std::string& filename) {
    auto start = std::chrono::system_clock::now();
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return ""; // Return empty string if file couldn't be opened
    }

    // Determine the size of the file
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the file into a string buffer
    std::string fileContent;
    fileContent.resize(fileSize);
    if (!file.read(&fileContent[0], fileSize)) {
        std::cerr << "Failed to read file: " << filename << std::endl;
        return ""; // Return empty string if file read fails
    }
    auto stop = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = stop-start;
    std::cout << "temps de lecture du fichier " << filename << " : " << seconds << std::endl;

    return fileContent;
}