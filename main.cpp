#include <X11/Xlib.h>
#include <iostream>
#include <bits/stdc++.h>

#include "Config/MyshConfig.h"
#include "Macro/Macro.h"
#include "System/X11System.h"

void print_debug(std::string_view message);


bool debugMode = true; //todo: implement parameters and debugging
X11System currentSystem;

int main() {
    if (!currentSystem.isEnabled) {
        std::cerr << currentSystem.errorMessage << std::endl;
    }

    MyshConfig conf;
    if (!conf.isEnabled) {
        std::cerr << conf.errorMessage << std::endl;
        return 1;
    }

    /* LMB = 1,RMB = 3, MMB = 2 scrollD = 5,ScrollU = 4,Thumb1 = 8,Thumb2 = 9,Finger1 = 12,Finger2 = 13 */

    print_debug("Myshkin initialized...");

    for (auto i{conf.macros.begin()}; i != conf.macros.end(); ++i) {
        currentSystem.grabMouse(i->first);
    }

    XEvent event;
    while (true) {
        XNextEvent(currentSystem.getDisplay(), &event);

        //https://gist.github.com/pioz/726474 todo: use for reference
        if (event.type == ButtonPress && conf.hasTrigger(event.xbutton.button)) {
            conf.macros[event.xbutton.button]->execute();
        }
    }
}

void print_debug(const std::string_view message) {
    if (debugMode) {
        std::cout << message << std::endl;
    }
}