#ifndef MYSHKIN_MOUSE_H
#define MYSHKIN_MOUSE_H

#include <string>

#include "./Device.h"

class Mouse : Device {
private:
    static constexpr int ACTION_PRESS_DOWN{1};
    static constexpr int ACTION_RELEASE{0};

public:
    bool isEnabled;
    Mouse(std::string devId);
    Mouse();
    void close();
    libevdev* getDevice() const;
};



#endif //MYSHKIN_MOUSE_H
