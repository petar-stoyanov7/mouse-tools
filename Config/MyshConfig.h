#ifndef MYSHKIN_MYSHCONFIG_H
#define MYSHKIN_MYSHCONFIG_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "../Macro/Macro.h"
#include "../Device/Mouse.h"
#include "../Device/Keyboard.h"

extern Mouse mouse;
extern Keyboard keyboard;

class MyshConfig {
public:
    std::map<int, std::unique_ptr<Macro>> macros;
    bool isEnabled{true};
    std::string errorMessage;

    MyshConfig(std::string path = "");
    bool hasTrigger(unsigned int key);

};

#endif //MYSHKIN_MYSHCONFIG_H
