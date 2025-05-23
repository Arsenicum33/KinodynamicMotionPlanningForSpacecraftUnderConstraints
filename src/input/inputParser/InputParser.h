// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef INPUTPARSER_H
#define INPUTPARSER_H
#include <string>
#include <stdexcept>
#include <filesystem>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <dto/envSettings/EnvSettings.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "dto/envSettings/EnvSettingsAstroRaw.h"
#include "dto/envSettings/EnvSettingsRaw.h"
#include "utils/PhysicsUtils.h"

class InputParser
{
public:
    InputParser(int argc, char* argv[], bool useDefaultParameterValues = false);
    std::unique_ptr<EnvSettingsRaw> getEnvSettingsRaw();
private:
    void validateFilePath(const std::string& path, const std::string& fileType) const;
    std::unique_ptr<EnvSettingsRaw>  createDefaultEnvSettings();
    std::unique_ptr<EnvSettingsRaw>  createStaticEnvSettings();
    std::unique_ptr<EnvSettingsRaw>  createDynamicEnvSettings();
    std::unique_ptr<EnvSettingsRaw>  createMovingTargetEnvSettings();
    std::unique_ptr<EnvSettingsRaw>  createKinodynamicEnvSettings();
    std::unique_ptr<EnvSettingsAstroRaw>  createAstrodynamicEnvSettings();
    std::unique_ptr<EnvSettingsAstroRaw>  createAstrodynamicEnvSettings1();
    std::unique_ptr<EnvSettingsRaw>  createEnvSettingsFromFile(const std::string& filepath);
    std::shared_ptr<Pose> parseStart(const Json::Value& json);
    std::array<double, 3> parseJsonArrayOfDoubles(const Json::Value& json);
    std::vector<std::string> parseJsonVectorOfStrings(const Json::Value& json);
    std::shared_ptr<State> computeStartRelativeToOrigin(std::shared_ptr<Pose> start,
        std::unordered_map<std::string, std::any> celestialBodyProperties);
    std::unordered_map<std::string, std::unordered_map<std::string, std::any>>  parseCelestialBodiesFromFile(const std::string& filepath);
    std::unordered_map<std::string, std::unordered_map<std::string, std::any>>  parseCelestialBodies(const Json::Value& json);
    std::unique_ptr<EnvSettingsRaw> envSettings;

};




#endif //INPUTPARSER_H
