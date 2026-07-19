#include "VirtualMouse.h"

VirtualMouse::VirtualMouse() {
    struct libevdev* dev = libevdev_new();
    libevdev_set_name(dev, "Virtual Mouse");

    libevdev_enable_property(dev, INPUT_PROP_POINTER);

    libevdev_enable_event_type(dev, EV_REL);
    libevdev_enable_event_code(dev, EV_REL, REL_X, nullptr);
    libevdev_enable_event_code(dev, EV_REL, REL_Y, nullptr);
    libevdev_enable_event_code(dev, EV_REL, REL_WHEEL, nullptr);

    libevdev_enable_event_type(dev, EV_KEY);
    libevdev_enable_event_code(dev, EV_KEY, BTN_LEFT, nullptr);
    libevdev_enable_event_code(dev, EV_KEY, BTN_RIGHT, nullptr);
    libevdev_enable_event_code(dev, EV_KEY, BTN_MIDDLE, nullptr);

    const int r = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &m_uinput);
    is_enabled = (r == 0);
    libevdev_free(dev);
}

VirtualMouse::~VirtualMouse() {
    libevdev_uinput_destroy(m_uinput);
}

void VirtualMouse::click(int key, bool is_down) {
    std::lock_guard<std::mutex> guard(m_mouseMutex);
    libevdev_uinput_write_event(m_uinput, EV_KEY, key, is_down);
    libevdev_uinput_write_event(m_uinput, EV_SYN, SYN_REPORT, 0);
}

void VirtualMouse::move(int x, int y) {
    //moves relative to current cursor
    std::lock_guard<std::mutex> guard(m_mouseMutex);
    libevdev_uinput_write_event(m_uinput, EV_REL, REL_X, x);
    libevdev_uinput_write_event(m_uinput, EV_REL, REL_Y, y);
    libevdev_uinput_write_event(m_uinput, EV_SYN, SYN_REPORT, 0);
}

void VirtualMouse::scroll(int val) {
    std::lock_guard<std::mutex> guard(m_mouseMutex);
    libevdev_uinput_write_event(m_uinput, EV_REL, REL_WHEEL, val);
    libevdev_uinput_write_event(m_uinput, EV_SYN, SYN_REPORT, 0);
}
