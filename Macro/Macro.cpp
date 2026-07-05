#include "Macro.h"

#include <iostream>
#include <chrono>
#include <thread>

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

//todo: get mouse in macro

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
            toggleHold();
            std::cout << "hold" << std::endl; //todo: implement
            break;
        default:
            return;
    }
}
void Macro::toggleSpam() {
    std::cout << "toggle spam" << std::endl;
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

void Macro::toggleHold() {
    if (running_) {
        running_ = false;
        if (thread_.joinable()) {
            thread_.join();
        }
    } else {
        running_ = true;
        thread_ = std::thread(&Macro::hold, this);
    }
}

void Macro::spam() {
    while (running_) {
        if (type == MACRO_TYPE_MOUSE) {
            std::cout << "mouse click: " << key << std::endl;
            //todo: add mouse click
        }
        //todo: implement keyboard
        // std::cout << "spam mouse clicks --> trigger:" << trigger << " , key: " << key <<  std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay)); //sleep for X milliseconds
    }
}

void Macro::hold() {
    std::cout << "hold key: " << key << std::endl;
    //todo: implement
}