#include "MyshConfig.h"
#include <fstream>

using nlohmann::json;

MyshConfig::MyshConfig(std::string path) : mouse(), keyboard() {
    path = path.empty() ? "../config.json" : path; //todo: add proper config path
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

    json config, macroData;

    try {
        config = json::parse(f);
        macroData = config["macros"];

        mouse = Mouse(config["mouse"]);
        if (mouse.isEnabled == false) {
            isEnabled = false;
            errorMessage = "Mouse is not properly configured";
            return;
        }

        keyboard = Keyboard(config["keyboard"]);
        if (keyboard.isEnabled == false) {
            isEnabled = false;
            errorMessage = "Keyboard is not properly configured";
            return;
        }
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

        macros.emplace(
            macroData[i]["trigger"],
            std::make_unique<Macro>(
                macroData[i]["trigger"],
                macroData[i]["action"],
                macroData[i]["type"],
                macroData[i]["key"],
                macroData[i]["delay"],
                macroData[i]["duration"]
            )
        );
    }
}

bool MyshConfig::hasTrigger(unsigned int key) {
    return macros.contains(key);
}
