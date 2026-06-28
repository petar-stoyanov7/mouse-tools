#include <iostream>
#include <bits/stdc++.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <stdio.h>

#include "Config/MyshConfig.h"
#include "Macro/Macro.h"


void print_debug(std::string_view message);

bool debugMode = true; //todo: implement parameters and debugging

int main() {
    MyshConfig config;
    if (!config.isEnabled) {
        std::cerr << config.errorMessage << std::endl;
        return 1;
    }

    struct input_event ev;
    while (true) {
        read(config.mouse.fd, &ev, sizeof(ev));
        if (ev.type == EV_KEY) {
            if (ev.code == BTN_LEFT || ev.code == BTN_MIDDLE || ev.code == BTN_RIGHT) { //no macros on left, right, middle
                continue;
            }
            std::cout << "Mouse clicked: " << ev.code << std::endl;
        }
        /* keep as an example of detected mouse click*/
        // if (ev.type == EV_KEY && ev.code == BTN_LEFT) {
        //     printf("Left click: %s\n", ev.value ? "down" : "up");
        // }

        /* example of mouse movement*/
        // if (ev.type == EV_REL) {
        //     if (ev.code == REL_X) printf("Mouse X: %d\n", ev.value);
        //     if (ev.code == REL_Y) printf("Mouse Y: %d\n", ev.value);
        // }

    }
    
    // print_debug("Myshkin initialized...");
    //
    // for (auto i{conf.macros.begin()}; i != conf.macros.end(); ++i) {
    //     currentSystem.grabMouse(i->first);
    // }
    //
    // XEvent event;
    // while (true) {
    //     XNextEvent(currentSystem.getDisplay(), &event);
    //
    //     //https://gist.github.com/pioz/726474 todo: use for reference
    //     if (event.type == ButtonPress && conf.hasTrigger(event.xbutton.button)) {
    //         conf.macros[event.xbutton.button]->execute();
    //     }
    // }
}

void print_debug(const std::string_view message) {
    if (debugMode) {
        std::cout << message << std::endl;
    }
}