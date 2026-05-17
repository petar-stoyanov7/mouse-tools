#ifndef MYSHKIN_MACRO_H
#define MYSHKIN_MACRO_H

#include <nlohmann/json.hpp>

class Macro {
private:
    bool isActive{false};
    void spamButton();
    int action; //type of macro - spam, hold, etc
    int type; //mouse or keyboard
    int key; //key/button to use
    double delay; //delay between repetitions (for spam)
    double duration; //max duration for the macro
public:
    int trigger; //the button/combination to trigger the macro

    static constexpr int MACRO_TYPE_MOUSE {1};
    static constexpr int MACRO_TYPE_KEYBOARD {2};

    static constexpr int MACRO_ACTION_SPAM {1};
    static constexpr int MACRO_ACTION_HOLD {2};

    Macro(int trigger, int action, int type, int key, double delay, double duration);
    static bool isValidMacro(nlohmann::json entry);

    void execute();

};

#endif //MYSHKIN_MACRO_H
