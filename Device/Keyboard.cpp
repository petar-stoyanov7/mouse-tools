#include "Keyboard.h"

Keyboard::Keyboard(std::string deviceName) {
    dev = find_device_by_name(deviceName);
    if (dev == nullptr) {
        isEnabled = false;
        return;
    }
    isEnabled = true;
    printDeviceDebug("Keyboard");
}

Keyboard::Keyboard() {
    dev = nullptr;
    isEnabled = false;
}

libevdev* Keyboard::getDevice() const {
    return Device::getDevice();
}