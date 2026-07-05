#ifndef MYSHKIN_MOUSE_H
#define MYSHKIN_MOUSE_H

#include <string>
#include <string.h>

#include "./Device.h"

class Mouse : Device {
private:
    static constexpr int ACTION_PRESS_DOWN{1};
    static constexpr int ACTION_RELEASE{0};
    void emit(int type, int code, int value);

public:
    bool isEnabled;
    Mouse(std::string devId);
    Mouse();
    void click(int button);
    void press(int button, int action);
    libevdev* getDevice() const;
};



#endif //MYSHKIN_MOUSE_H
