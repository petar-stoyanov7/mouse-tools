#ifndef MYSHKIN_KEYBOARD_H
#define MYSHKIN_KEYBOARD_H
#include <string>

#include "./Device.h"

class Keyboard : Device {
public:
    bool isEnabled;
    Keyboard(std::string deviceName);
    Keyboard();
    libevdev* getDevice() const;
};



#endif //MYSHKIN_KEYBOARD_H
