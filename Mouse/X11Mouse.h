#ifndef MYSHKIN_MOUSE_H
#define MYSHKIN_MOUSE_H

#include <X11/Xlib.h>
#include "../System/X11System.h"

class X11Mouse {
public:
    void static grabMouse(X11System sys, int button);
};



#endif //MYSHKIN_MOUSE_H
