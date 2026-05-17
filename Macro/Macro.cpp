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
            if (!isActive) {
                isActive = true;
                spamButton(); //todo: implement async
            }
            break;
        case MACRO_ACTION_HOLD:
            std::cout << "hold" << std::endl; //todo: implement
            break;
        default:
            return;
    }
}

void Macro::spamButton() {
    time_t start = std::time(nullptr);
    while (std::time(nullptr) - start < this->duration) {
        std::cout << "click " << this->key << std::endl; //todo: replace with actual click
        sleep(this->delay);
    }
    isActive = false;
}