#include "X11System.h"

X11System::X11System() {
    display = XOpenDisplay(nullptr);
    if (!display) {
        isEnabled = false;
        errorMessage = "Cannot Open display";
    }

    window = DefaultRootWindow(display);
}

Display* X11System::getDisplay() const {
    return display;
}

Window X11System::getWindow() const {
    return window;
}