#include "VirtualKeyboard.h"

VirtualKeyboard::VirtualKeyboard() {
    struct libevdev* dev = libevdev_new();
    libevdev_set_name(dev, "Virtual Keyboard");

    libevdev_enable_property(dev, INPUT_PROP_POINTER);


    libevdev_enable_event_type(dev, EV_KEY);
    libevdev_enable_event_code(dev, EV_KEY, KEY_LEFTALT, nullptr);
    // libevdev_enable_event_code(dev, EV_KEY, BTN_RIGHT, nullptr);
    // libevdev_enable_event_code(dev, EV_KEY, BTN_MIDDLE, nullptr);

    const int r = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &k_uinput);
    is_enabled = (r == 0);
    libevdev_free(dev);
}

VirtualKeyboard::~VirtualKeyboard() {
    libevdev_uinput_destroy(k_uinput);
}

void VirtualKeyboard::key_press(int key, bool is_down) {
    std::lock_guard<std::mutex> guard(m_keyboardMutex);
    libevdev_uinput_write_event(k_uinput, EV_KEY, key, is_down);
    libevdev_uinput_write_event(k_uinput, EV_SYN, SYN_REPORT, 0);
}
