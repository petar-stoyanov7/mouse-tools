#ifndef MYSHKIN_MYSHCONFIG_H
#define MYSHKIN_MYSHCONFIG_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "../Macro/Macro.h"

class MyshConfig {
private:
    std::vector<Macro> macros;

public:
    std::vector<int> triggers;
    bool isEnabled{true};
    std::string errorMessage;

    MyshConfig(std::string path = "");
    bool hasTrigger(int key);
};

#endif //MYSHKIN_MYSHCONFIG_H
