#ifndef MYSHKIN_VIRTUALMOUSE_H
#define MYSHKIN_VIRTUALMOUSE_H

#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <mutex>
#include <vector>

class VirtualDevice {
public:
    VirtualDevice();
    ~VirtualDevice();
    explicit VirtualDevice(const std::vector<int> &macroKeys);
    void move(int x, int y);
    void press(int key, bool isDown);
    void scroll(int val);
private:
    bool isEnabled = false;
    struct libevdev_uinput* m_uinput = nullptr;
    std::mutex m_mouseMutex;
};

#endif //MYSHKIN_VIRTUALMOUSE_H
