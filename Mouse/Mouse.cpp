#include "Mouse.h"

Mouse::Mouse(const std::string &deviceName) {
    dev = find_mouse_by_name(deviceName);
    if (dev == nullptr) {
        isEnabled = false;
        return;
    }

    isEnabled = true;
    printMouseDebug("Mouse");
}

Mouse::Mouse() {
    dev = nullptr;
    isEnabled = false;
}

libevdev* Mouse::getMouse() const {
    return dev;
}

void Mouse::printMouseDebug(std::string type) {
    if (debugMode) {
        std::cout << type << ": " << libevdev_get_name(dev) <<  std::endl;
    }
}

struct libevdev *Mouse::find_mouse_by_name(const std::string &name) {
    struct libevdev *dev = nullptr;

    int failed = 0;

    for (int i = 0;; i++) {
        std::string path = "/dev/input/event" + std::to_string(i);
        int fd {
            open (path.c_str(), O_RDONLY | O_NONBLOCK)
        };
        if (fd == -1) {
            failed++;
        }

        if (libevdev_new_from_fd(fd, &dev) == 0) {
            std::string deviceName = libevdev_get_name(dev);
            if (deviceName == name) {
                return dev;
            }
            libevdev_free(dev);
            dev = nullptr;
        }

        if (failed > 3) {
            break;
        }
    }

    return dev;
}

void Mouse::close() {
    libevdev_free(dev);
}