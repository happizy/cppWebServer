#include "defaultController.h"
#include <filesystem>
#include <iostream>

const std::string CONTROLLER_NAME{"default"};
const std::string VIEW_PATH{"../view/"+CONTROLLER_NAME};
const std::string ASSET_PATH{"../asset/"+CONTROLLER_NAME};

std::pair<Doctype, std::string> hello_world(const std::string& resource) {
     std::stringstream response;
     return std::pair<Doctype, std::string> {TEXT, "Hello world !"};
}

std::pair<Doctype, std::string> index(const std::string& resource) {
    return std::pair<Doctype, std::string> {HTML, read_file(VIEW_PATH+"/Index.html")};
}

std::pair<Doctype, std::string> get_default_asset(const std::string& resource) {
    if (resource.ends_with(".webp")) return std::pair<Doctype, std::string> {WEBP, read_file(ASSET_PATH+"/"+resource)};
    if (resource.ends_with(".css")) return std::pair<Doctype, std::string> {CSS, read_file(ASSET_PATH+"/"+resource)};
    return std::pair<Doctype, std::string> {TEXT, "hello resource seeker"};
}

