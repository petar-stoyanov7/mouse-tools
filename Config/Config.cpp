#include "Config.h"
#include <fstream>

using nlohmann::json;

Config::Config(std::string path) {
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

        mouse_name = config["mouse"].get<std::string>();
    } catch (const json::parse_error e) {
        isEnabled = false;
        errorMessage = e.what();
        return;
    }

    std::vector<int> macro_keys;
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

        macro_keys.push_back(macroData[i]["key"]);
    }

    v_device.~VirtualDevice();
    new(&v_device) VirtualDevice(macro_keys);
}

bool Config::hasTrigger(unsigned int key) {
    return macros.contains(key);
}

Mouse Config::getMouse() {
    return Mouse(mouse_name);
}