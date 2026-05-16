#include "MyshConfig.h"

using nlohmann::json;

MyshConfig::MyshConfig(std::string path) {
    path = path.empty() ? "../macros.json" : path; //todo: add proper config path
    if (!std::filesystem::exists(path)) {
        isEnabled = false;
        errorMessage = "Configuration file is missing";
        return;
    }

    std::fstream f(path);
    if (!f.is_open()) {
        isEnabled = false;
        errorMessage = "Could not open file";
        return;
    }

    json macroData;

    try {
        macroData = json::parse(f);
    } catch (const json::parse_error e) {
        isEnabled = false;
        errorMessage = e.what();
        return;
    }

    for (int i{0}; i < macroData.size(); ++i) {
        if (!Macro::isValidMacro(macroData[i])) {
            errorMessage = "Invalid macro entry: " + macroData[i].get<std::string>();
            isEnabled = false;
            return;
        }

        triggers.push_back(macroData[i]["trigger"]);

        const Macro macro = Macro(
            macroData[i]["trigger"],
            macroData[i]["action"],
            macroData[i]["type"],
            macroData[i]["key"],
            macroData[i]["delay"],
            macroData[i]["duration"]
        );

        macros.push_back(macro);
    }
}

bool MyshConfig::hasTrigger(int key) {
    if (std::ranges::count(triggers, key) > 0) {
        return true;
    }

    return false;
}




