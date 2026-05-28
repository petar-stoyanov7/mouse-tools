#include "X11Mouse.h"

void X11Mouse::grabMouse(X11System sys, int button) {
    XGrabButton(sys.getDisplay(), button, AnyModifier, sys.getWindow(), True,
                ButtonPressMask | ButtonReleaseMask,
                GrabModeAsync, GrabModeAsync, None, None);
}
