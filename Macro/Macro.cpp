#include "Macro.h"

#include <iostream>


Macro::Macro(
    const int trigger,
    const int action,
    const int type,
    const int key,
    const double delay,
    const double duration
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
    switch (this->action) {
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

void Macro::startSpam() {
    if (running_) {
        return;
    }

    running_ = true;
    thread_ = std::thread(&Macro::spam, this);
}

void Macro::stopSpam() {
    if (!running_) {
        return;
    }

    running_ = false;
    if (thread_.joinable()) {
        thread_.join();
    }
}

void Macro::toggleSpam() {
    if (running_) {
        stopSpam();
    } else {
        startSpam();
    }
}

void Macro::spam() {
    //todo: add actual clicks
    while (running_) {
        std::cout << "spam mouse clicks --> button:" << key <<  std::endl;
        sleep(delay);
    }
}