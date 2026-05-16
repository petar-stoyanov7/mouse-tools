#include <X11/Xlib.h>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "Config/MyshConfig.h"

void print_debug(std::string_view message);

bool debugMode = true; //todo: implement parameters and debugging

int main() {
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Cannot open display\n";
        return 1;
    }
    const Window root = DefaultRootWindow(display);

    MyshConfig conf;
    if (!conf.isEnabled) {
        std::cerr << conf.errorMessage << std::endl;
        return 1;
    }

    /* LMB = 1,RMB = 3, MMB = 2 scrollD = 5,ScrollU = 4,Thumb1 = 8,Thumb2 = 9,Finger1 = 12,Finger2 = 13 */

    print_debug("Myshkin initialized...");

    //todo: implement configurator to get button values
    for (std::size_t i{0}; i < conf.triggers.size(); i++) {
        XGrabButton(display, conf.triggers[i], AnyModifier, root, True,
                ButtonPressMask | ButtonReleaseMask,
                GrabModeAsync, GrabModeAsync, None, None);
    }


    XEvent event;
    while (true) {
        XNextEvent(display, &event);

        if (event.type == ButtonPress) {
            if (conf.hasTrigger(event.xbutton.button)) {
                std::cout << "Button " << event.xbutton.button << " pressed!" << std::endl;
            }
        }
    }

    return 0;
}

void print_debug(const std::string_view message) {
    if (debugMode) {
        std::cout << message << std::endl;
    }
}