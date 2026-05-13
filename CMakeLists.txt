cmake_minimum_required(VERSION 4.2)
project(myshkin)

set(CMAKE_CXX_STANDARD 20)

# Find the X11 package
find_package(X11 REQUIRED)

add_executable(myshkin main.cpp)

# Link against X11
target_link_libraries(myshkin PRIVATE X11)