#include "Mouse.h"

Mouse::Mouse(std::string devId) {
    fd = open(devId.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        isEnabled = false;
    }
}

Mouse::Mouse() {
    fd = -1;
    isEnabled = false;
}
