cmake_minimum_required(VERSION 4.2)
project(myshkin)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_search_module(LIBEVDEV REQUIRED libevdev)

add_executable(myshkin main.cpp
        Config/Config.cpp
        Config/Config.h
        Macro/Macro.cpp
        Macro/Macro.h
        Mouse/Mouse.cpp
        Mouse/Mouse.h
        VirtualDevice/VirtualDevice.cpp
        VirtualDevice/VirtualDevice.h
)

target_include_directories(myshkin PRIVATE ${LIBEVDEV_INCLUDE_DIRS})
target_link_libraries(myshkin PRIVATE ${LIBEVDEV_LIBRARIES})