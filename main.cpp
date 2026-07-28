#include <iostream>
#include <bits/stdc++.h>
#include <linux/input.h>
#include <unistd.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <grp.h>

#include "Config/Config.h"
#include "Macro/Macro.h"
#include "Mouse/Mouse.h"
#include "VirtualDevice/VirtualKeyboard.h"
#include "VirtualDevice/VirtualDevice.h"

void print_debug(std::string_view message);

bool debugMode = true; //todo: implement parameters and debugging

VirtualDevice v_device;
input_event ev{};

int main() {
    Mouse mouse;
    Config config;
    if (config.isEnabled == false) {
        std::cerr << config.errorMessage << std::endl;
        return 1;
    }

    //workaround to run for normal user
    auto grp = getgrnam("input");
    if (grp == nullptr) {
        std::cerr << "get group name failed" << std::endl;
        return 1;
    }
    int oldgid = getgid();
    if (setgid(grp->gr_gid) < 0) {
        std::cerr << "Couldn't change group to input" << std::endl;
        return 1;
    }

    mouse = config.getMouse();
    if (mouse.isEnabled == false) {
        std::cerr << "Could not initialize mouse" << std::endl;
        return 1;
    }

    if (setgid(oldgid) < 0) {
        std::cerr << "Couldn't change to old group" << std::endl;
        return 1;
    }

    print_debug("Myshkin initialized...");

    int status = 0;
    auto is_error = [](int v) { return v < 0 && v != -EAGAIN; };
    auto has_next_event = [](int v) {
        return v >= 0;
    };
    const auto flags = LIBEVDEV_READ_FLAG_NORMAL | LIBEVDEV_READ_FLAG_BLOCKING;

    while (status = libevdev_next_event(mouse.getMouse(), flags, &ev), !is_error(status)) {
        if (!has_next_event(status)) {
            continue;
        }

        if (ev.type != EV_KEY) {
            continue;
        }

        if (ev.type == EV_KEY) {
            //std::cout << "b: " << KEY_A << std::endl; //todo debug message to show key code
            if (ev.code == BTN_LEFT || ev.code == BTN_RIGHT || ev.code == BTN_MIDDLE) {
                continue;
            }
            if (ev.value == 0 && config.hasTrigger(ev.code)) {
                std::cout << "Real mouse click: " << ev.code << std::endl;
                config.macros[ev.code]->execute();
            }
        }
    }

    mouse.close();
}

void print_debug(const std::string_view message) {
    if (debugMode) {
        std::cout << message << std::endl;
    }
}