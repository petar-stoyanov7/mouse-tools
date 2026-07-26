cmake_minimum_required(VERSION 4.2)
project(myshkin)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_search_module(LIBEVDEV REQUIRED libevdev)

add_executable(myshkin main.cpp
        Config/MyshConfig.cpp
        Config/MyshConfig.h
        Macro/Macro.cpp
        Macro/Macro.h
        Mouse/Mouse.cpp
        Mouse/Mouse.h
        VirtualDevice/VirtualMouse.cpp
        VirtualDevice/VirtualMouse.h
        VirtualDevice/VirtualKeyboard.cpp
        VirtualDevice/VirtualKeyboard.h
)

target_include_directories(myshkin PRIVATE ${LIBEVDEV_INCLUDE_DIRS})
target_link_libraries(myshkin PRIVATE ${LIBEVDEV_LIBRARIES})