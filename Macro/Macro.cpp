#include "Macro.h"

#include <iostream>
#include <chrono>
#include <thread>

#include "../System/X11System.h"

extern X11System currentSystem;

Macro::Macro(
    const int trigger,
    const int action,
    const int type,
    const int key,
    const int delay,
    const int duration
) {
    this->trigger = trigger;
    this->action = action;
    this->type = type;
    this->key = key;
    this->delay = delay;
    this->duration = duration;
}

bool Macro::isValidMacro(nlohmann::json entry) {
    if (
        entry["trigger"].is_number() &&
        entry["action"].is_number() &&
        entry["type"].is_number() &&
        entry["key"].is_number() &&
        entry["delay"].is_number() &&
        entry["duration"].is_number()
    ) {
        return true;
    }
    return false;
}

void Macro::execute() {
    switch (action) {
        case MACRO_ACTION_SPAM:
            toggleSpam();
            break;
        case MACRO_ACTION_HOLD:
            std::cout << "hold" << std::endl; //todo: implement
            break;
        default:
            return;
    }
}
void Macro::toggleSpam() {
    if (running_) {
        running_ = false;
        if (thread_.joinable()) {
            thread_.join();
        }
    } else {
        running_ = true;
        thread_ = std::thread(&Macro::spam, this);
    }
}

void Macro::spam() {
    //todo: add actual clicks
    while (running_) {
        if (type == MACRO_TYPE_MOUSE) {
            currentSystem.clickMouseButton(key);
        }
        // std::cout << "spam mouse clicks --> trigger:" << trigger << " , key: " << key <<  std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay)); //sleep for X milliseconds
    }
}