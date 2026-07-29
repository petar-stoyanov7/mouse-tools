#ifndef MYSHKIN_MOUSE_H
#define MYSHKIN_MOUSE_H

#include <string>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

extern bool debugMode;

class Mouse {
private:
    static constexpr int ACTION_PRESS_DOWN{1};
    static constexpr int ACTION_RELEASE{0};
private:
    struct libevdev *dev;
    struct libevdev* find_mouse_by_name(const std::string& name);
    void printMouseDebug(std::string type);

public:
    bool isEnabled;
    Mouse(const std::string &devId);
    Mouse();
    void close();
    libevdev* getMouse() const;
};

#endif //MYSHKIN_MOUSE_H
