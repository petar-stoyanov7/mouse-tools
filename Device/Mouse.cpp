#include "Mouse.h"

Mouse::Mouse(std::string deviceName) {
    dev = find_device_by_name(deviceName);
    if (dev == nullptr) {
        isEnabled = false;
        return;
    }

    isEnabled = true;
    printDeviceDebug("Mouse");
}

Mouse::Mouse() {
    dev = nullptr;
    isEnabled = false;
}

libevdev* Mouse::getDevice() const {
    return Device::getDevice();
}

void Mouse::close() {
    Device::close();
}