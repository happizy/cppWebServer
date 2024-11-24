cmake_minimum_required(VERSION 3.28)
project(webServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MINIMUM_REQUIRED_VERSION TRUE)

add_executable(webServer main.cpp server/clientHandle.cpp server/routingLogic.cpp
         controller/default/defaultController.cpp
        server/controllerLogic.h)
target_link_libraries(webServer ws2_32)
