# cppWebServer

cppWebServer is a simple web server implemented in C++.

https://github.com/user-attachments/assets/534452e3-a7ed-48e4-97d7-c210c9081c6f


## Features

- Serves static web pages
- Handles basic HTTP requests

## Requirements

- C++ compiler (e.g., GCC)
- CMake
- Make

## Installation

```bash
git clone https://github.com/happizy/cppWebServer.git
```
Compile the server using the CMake file and run the executable.
By default, the address is set to localhost 8080.

## Available URLs
- `/` will return hello world
- `/assets/default` will display a message made to assert assets are reachable
- `/index` will display the view associated with the default controller (see video above)
