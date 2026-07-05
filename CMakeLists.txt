cmake_minimum_required(VERSION 4.2)
project(myshkin)

set(CMAKE_CXX_STANDARD 20)

# Find the X11 package todo: remove
find_package(X11 REQUIRED)
pkg_check_modules(libevdev2 REQUIRED)

add_executable(myshkin main.cpp
        Config/MyshConfig.cpp
        Config/MyshConfig.h
        Macro/Macro.cpp
        Macro/Macro.h
        Device/Keyboard.cpp
        Device/Keyboard.h
        Device/Mouse.cpp
        Device/Mouse.h
        Device/Device.cpp
        Device/Device.h
)

target_link_libraries(myshkin PRIVATE evdev2)