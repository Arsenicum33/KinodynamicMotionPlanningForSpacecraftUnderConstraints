//
// Created by arseniy on 24.10.24.
//

#ifndef INPUTPARSER_H
#define INPUTPARSER_H
#include <string>
#include <stdexcept>
#include <filesystem>
#include <jsoncpp/json/json.h>
#include <fstream>

#include "dto/EnvSettingsRaw.h"

class InputParser
{
public:
    InputParser(int argc, char* argv[], bool useDefaultParameterValues = false);
    const EnvSettingsRaw& getEnvSettingsRaw();
private:
    void validateFilePath(const std::string& path, const std::string& fileType) const;
    EnvSettingsRaw createDefaultEnvSettings();
    EnvSettingsRaw createEnvSettingsFromFile(const std::string& filepath);
    std::array<double, 3> parseJsonArrayOfDoubles(const Json::Value& json);
    std::vector<std::string> parseJsonVectorOfStrings(const Json::Value& json);
    EnvSettingsRaw envSettings;
};



#endif //INPUTPARSER_H
