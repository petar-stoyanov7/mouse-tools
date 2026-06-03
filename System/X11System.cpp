#include "X11System.h"

#include <cstring>
#include <iostream> //todo: remove

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

void X11System::grabMouse(int button) {
    XGrabButton(display, button, AnyModifier, window, True,
                ButtonPressMask | ButtonReleaseMask,
                GrabModeAsync, GrabModeAsync, None, None);
}

void X11System::clickMouseButton(int button) {
    // Create and setting up the event
    XEvent event;
    memset (&event, 0, sizeof (event));
    event.xbutton.button = button;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow (display);
    while (event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer (display, event.xbutton.window,
               &event.xbutton.root, &event.xbutton.subwindow,
               &event.xbutton.x_root, &event.xbutton.y_root,
               &event.xbutton.x, &event.xbutton.y,
               &event.xbutton.state);
    }

    event.type = ButtonPress;
    if (XSendEvent (display, PointerWindow, True, ButtonPressMask, &event) == 0) {
        fprintf (stderr, "Error to send the event!\n");
    }
    XFlush (display);
    // Release
    event.type = ButtonRelease;
    if (XSendEvent (display, PointerWindow, True, ButtonReleaseMask, &event) == 0) {
        fprintf (stderr, "Error to send the event!\n");
    }
    XFlush (display);
}