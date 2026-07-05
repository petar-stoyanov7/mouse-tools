#ifndef MYSHKIN_MACRO_H
#define MYSHKIN_MACRO_H

#include <nlohmann/json.hpp>
#include <atomic>
#include <thread>
#include "../Device/Mouse.h"

extern Mouse mouse;

class Macro {
private:
    bool isActive{false};
    int action; //type of macro - spam, hold, etc
    int type; //mouse or keyboard
    int key; //key/button to use
    int delay; //delay in milliseconds between repetitions (for spam)
    int duration; //max duration in seconds for the macro

    std::atomic<bool> running_{false};
    std::thread thread_;

    void toggleSpam();
    void toggleHold();
    void spam();
    void hold();
public:
    int trigger; //the button/combination to trigger the macro

    static constexpr int MACRO_TYPE_MOUSE {1};
    static constexpr int MACRO_TYPE_KEYBOARD {2};

    static constexpr int MACRO_ACTION_SPAM {1};
    static constexpr int MACRO_ACTION_HOLD {2};

    Macro(int trigger, int action, int type, int key, int delay, int duration);
    static bool isValidMacro(nlohmann::json entry);

    void execute();
};

#endif //MYSHKIN_MACRO_H
