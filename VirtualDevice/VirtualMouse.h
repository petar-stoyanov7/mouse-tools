#ifndef MYSHKIN_VIRTUALMOUSE_H
#define MYSHKIN_VIRTUALMOUSE_H
#include "../Device/Device.h"

#include <iostream>
#include <string>
#include <mutex>
#include <set>
#include <thread>
#include <chrono>
#include <atomic>
#include <unistd.h>
#include <fcntl.h>
#include <grp.h>


class VirtualMouse : Device {
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
