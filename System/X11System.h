#ifndef MYSHKIN_X11SYSTEM_H
#define MYSHKIN_X11SYSTEM_H

#include <string>
#include <X11/Xlib.h>

class X11System {
private:
    Display* display;
    Window window;

public:
    bool isEnabled{true};
    std::string errorMessage;
    X11System();
    Display* getDisplay() const;
    Window getWindow() const;
};



#endif //MYSHKIN_X11SYSTEM_H
