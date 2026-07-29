#ifndef MYSHKIN_MYSHCONFIG_H
#define MYSHKIN_MYSHCONFIG_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "../Macro/Macro.h"
#include "../Mouse/Mouse.h"

extern Mouse mouse;
extern VirtualDevice v_device;

class Config {
public:
    std::map<int, std::unique_ptr<Macro>> macros;
    bool isEnabled{true};
    std::string errorMessage;

    Config(std::string path = "");
    bool hasTrigger(unsigned int key);
    Mouse getMouse();
private:
    std::string mouseName;
};

#endif //MYSHKIN_MYSHCONFIG_H
