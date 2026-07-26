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
        if (type == MACRO_TYPE_MOUSE) {
            thread_ = std::thread(&Macro::mouse_spam, this);
        } else if (type == MACRO_TYPE_KEYBOARD) {
            thread_ = std::thread(&Macro::keyboard_spam, this);
        }
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

void Macro::mouse_spam() {
    while (running_) {
        v_mouse.click(key, true);
        usleep(1);
        v_mouse.click(key, false);

        std::this_thread::sleep_for(std::chrono::milliseconds(delay)); //sleep for X milliseconds
    }
}

void Macro::keyboard_spam() {
    while (running_) {
        v_keyboard.key_press(key, true);
        usleep(1);
        v_keyboard.key_press(key, false);

        std::this_thread::sleep_for(std::chrono::milliseconds(delay)); //sleep for X milliseconds
    }

}

void Macro::hold() {
    std::cout << "hold key: " << key << std::endl;
    //todo: implement
}