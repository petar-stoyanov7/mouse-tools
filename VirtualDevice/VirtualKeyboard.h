#ifndef MYSHKIN_VIRTUALKEYBOARD_H
#define MYSHKIN_VIRTUALKEYBOARD_H

#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <mutex>

class VirtualKeyboard {
public:
    VirtualKeyboard();
    ~VirtualKeyboard();
    void key_press(int key, bool is_down);
private:
    bool is_enabled;
    struct libevdev_uinput* k_uinput = nullptr;
    std::mutex m_keyboardMutex;
};



#endif //MYSHKIN_VIRTUALKEYBOARD_H
