#ifndef DEFAULT_CONTROLLER_H
#define DEFAULT_CONTROLLER_H

#include <string>
#include <sstream>
#include "../../server/routingLogic.h"

std::pair<Doctype, std::string> hello_world(const std::string& resource);
std::pair<Doctype, std::string> index(const std::string& resource);
std::pair<Doctype, std::string> get_default_asset(const std::string& resource);

#endif
