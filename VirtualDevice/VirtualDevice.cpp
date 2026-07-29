#include "VirtualDevice.h"

#include <vector>
VirtualDevice::VirtualDevice() {
    isEnabled = false;
}

VirtualDevice::VirtualDevice(const std::vector<int> &macroKeys) {
    struct libevdev* dev = libevdev_new();
    libevdev_set_name(dev, "Virtual Input Device");

    libevdev_enable_property(dev, INPUT_PROP_POINTER);

    libevdev_enable_event_type(dev, EV_REL);
    libevdev_enable_event_code(dev, EV_REL, REL_X, nullptr);
    libevdev_enable_event_code(dev, EV_REL, REL_Y, nullptr);
    libevdev_enable_event_code(dev, EV_REL, REL_WHEEL, nullptr);

    libevdev_enable_event_type(dev, EV_KEY);
    for (const int& key : macroKeys) {
        libevdev_enable_event_code(dev, EV_KEY, key, nullptr);
    }

    const int r = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &m_uinput);
    isEnabled = (r == 0);
    libevdev_free(dev);
}

VirtualDevice::~VirtualDevice() {
    libevdev_uinput_destroy(m_uinput);
}

void VirtualDevice::press(int key, bool isDown) {
    std::lock_guard<std::mutex> guard(m_mouseMutex);
    libevdev_uinput_write_event(m_uinput, EV_KEY, key, isDown);
    libevdev_uinput_write_event(m_uinput, EV_SYN, SYN_REPORT, 0);
}

void VirtualDevice::move(int x, int y) {
    //moves relative to current cursor
    std::lock_guard<std::mutex> guard(m_mouseMutex);
    libevdev_uinput_write_event(m_uinput, EV_REL, REL_X, x);
    libevdev_uinput_write_event(m_uinput, EV_REL, REL_Y, y);
    libevdev_uinput_write_event(m_uinput, EV_SYN, SYN_REPORT, 0);
}

void VirtualDevice::scroll(int val) {
    std::lock_guard<std::mutex> guard(m_mouseMutex);
    libevdev_uinput_write_event(m_uinput, EV_REL, REL_WHEEL, val);
    libevdev_uinput_write_event(m_uinput, EV_SYN, SYN_REPORT, 0);
}
