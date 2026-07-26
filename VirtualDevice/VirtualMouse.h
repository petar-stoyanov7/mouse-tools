#ifndef MYSHKIN_VIRTUALMOUSE_H
#define MYSHKIN_VIRTUALMOUSE_H

#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <mutex>

class VirtualMouse {
public:
    VirtualMouse();
    ~VirtualMouse();
    void move(int x, int y);
    void click(int key, bool is_down);
    void scroll(int val);
private:
    bool is_enabled = false;
    struct libevdev_uinput* m_uinput = nullptr;
    std::mutex m_mouseMutex;
};



#endif //MYSHKIN_VIRTUALMOUSE_H
