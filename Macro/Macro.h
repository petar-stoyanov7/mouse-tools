#ifndef MYSHKIN_MACRO_H
#define MYSHKIN_MACRO_H

#define MACRO_TYPE_MOUSE 1;
#define MACRO_TYPE_KBD 2;

#define MACRO_ACTION_SPAM 1;
#define MACRO_ACTION_HOLD 2;

#include <nlohmann/json.hpp>

class Macro {
public:
    int trigger;
    int action;
    int type;
    int key;
    double delay;
    double duration;

    Macro(int trigger, int action, int type, int key, double delay, double duration);
    static bool isValidMacro(nlohmann::json entry);
};

#endif //MYSHKIN_MACRO_H
