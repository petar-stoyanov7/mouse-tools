#include "Keyboard.h"

Keyboard::Keyboard(std::string devId) {
    fd = open(devId.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        isEnabled = false;
    }
}

Keyboard::Keyboard() {
    fd = -1;
    isEnabled = false;
}
