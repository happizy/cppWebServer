#ifndef ROUTING_LOGIC_H
#define ROUTING_LOGIC_H

#include <fstream>
#include <sstream>
#include <regex>

enum Doctype {
    TEXT,
    HTML,
    JSON,
    PNG,
    GIF,
    CSS,
    WEBP,
};

std::string read_file(const std::string& filename);

#endif