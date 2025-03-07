//
// Created by arseniy on 13.1.25.
//

#include "Reader.h"

#include <fileParsers/animationParsers/FbxParser.h>
#include <spdlog/spdlog.h>


ReaderContext Reader::run()
{
    EnvSettingsRaw envSettingsRaw = inputParser->getEnvSettingsRaw();
    EnvSettings envSettings = processRawEnvSettings(envSettingsRaw);
    std::vector<ComponentConfig> componentConfigs = componentsParser->getComponents();
    std::unordered_map<std::string, std::any> sharedVariables = componentsParser->getSharedVariables();

    spdlog::info("Input successful");

    return ReaderContext{
        std::move(envSettings),
        componentConfigs,
        sharedVariables
    };
}

EnvSettings Reader::processRawEnvSettings(const EnvSettingsRaw &rawSettings)
{
    Pose start = rawSettings.startPose;
    std::variant<Pose, std::shared_ptr<DynamicObject<RAPID_model>>> target;
    if (std::holds_alternative<Pose>(rawSettings.target))
    {
        target = std::get<Pose>(rawSettings.target);
    }
    else
    {
        target = animationParser->parse(std::get<std::string>(rawSettings.target));
    }
    ConfigurationSpaceBoundaries boundaries = rawSettings.boundaries;
    std::shared_ptr<RAPID_model> agent = std::move(meshParser->parse(rawSettings.agentFilepath)[0]);

    std::vector<std::shared_ptr<RAPID_model>> obstacles = meshParser->parse(rawSettings.obstaclesFilepath);
    std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    for (const std::string& filepath : rawSettings.dynamicObjectsFilepaths)
    {
        dynamicObjects.push_back(animationParser->parse(filepath));
    }

    return EnvSettings(start, target, agent, obstacles, dynamicObjects,boundaries);
}
