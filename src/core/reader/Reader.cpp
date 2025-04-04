//
// Created by arseniy on 13.1.25.
//

#include "Reader.h"

#include <spdlog/spdlog.h>

#include "dto/envSettings/EnvSettingsAstro.h"


ReaderContext Reader::run()
{
    std::unique_ptr<EnvSettingsRaw> envSettingsRaw = inputParser->getEnvSettingsRaw();
    std::string componentsFilepath = "../" + envSettingsRaw->componentsPresetFilename;
    spdlog::info("Using component preset {}", componentsFilepath);
    componentsParser = std::make_unique<ComponentsParser>(componentsFilepath);
    std::unique_ptr<EnvSettings> envSettings;
    EnvSettingsAstroRaw* envSettingsAstro = dynamic_cast<EnvSettingsAstroRaw*>(envSettingsRaw.get());
    if (envSettingsAstro != nullptr)
    {
        envSettings = processEnvSettingsAstroRaw(envSettingsAstro);
    }
    else
    {
        envSettings = processEnvSettingsRaw(envSettingsRaw.get());
    }
    std::vector<ComponentConfig> componentConfigs = componentsParser->getComponents();
    std::unordered_map<std::string, std::any> sharedVariables = componentsParser->getSharedVariables();

    spdlog::info("Input successful");

    return ReaderContext{
        std::move(envSettings),
        componentConfigs,
        sharedVariables
    };
}

std::unique_ptr<EnvSettings> Reader::processEnvSettingsRaw(EnvSettingsRaw* rawSettings)
{
    Pose start = rawSettings->startPose;
    std::variant<Pose, std::shared_ptr<DynamicObject<RAPID_model>>> target;
    if (std::holds_alternative<Pose>(rawSettings->target))
    {
        target = std::get<Pose>(rawSettings->target);
    }
    else
    {
        target = animationParser->parse(std::get<std::string>(rawSettings->target));
    }
    ConfigurationSpaceBoundaries boundaries = rawSettings->boundaries;
    std::shared_ptr<RAPID_model> agent = std::move(meshParser->parse(rawSettings->agentFilepath)[0]);

    std::vector<std::shared_ptr<RAPID_model>> obstacles = std::move(meshParser->parse(rawSettings->obstaclesFilepath));
    std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    for (const std::string& filepath : rawSettings->dynamicObjectsFilepaths)
    {
        dynamicObjects.push_back(animationParser->parse(filepath));
    }

    return std::make_unique<EnvSettings>(start, target, agent, obstacles, dynamicObjects,boundaries);
}

std::unique_ptr<EnvSettingsAstro> Reader::processEnvSettingsAstroRaw(EnvSettingsAstroRaw* rawSettings)
{
    std::unique_ptr<EnvSettings> envSettings = processEnvSettingsRaw(rawSettings);
    return std::make_unique<EnvSettingsAstro>(*(envSettings.release()), createCelestialBodies(rawSettings->celestialBodies));
}

std::vector<CelestialBody> Reader::createCelestialBodies(std::unordered_map<std::string, std::unordered_map<std::string, std::any>> celestialBodies) const
{
    std::vector<CelestialBody> result;
    for (const auto& [name, properties] : celestialBodies)
    {
        std::vector<double> times = std::any_cast<std::vector<double>>(properties.at("times"));
        std::vector<std::array<double, 3>> positions = std::any_cast<std::vector<std::array<double, 3>>>(properties.at("positions"));
        long double mass = std::any_cast<long double>(properties.at("mass"));
        std::vector<Keyframe> keyframes;
        for (int i=0;i<times.size();i++)
        {
            Keyframe keyframe(positions[i], times[i]);
            keyframes.push_back(keyframe);
        }
        std::shared_ptr<Animation> animation = std::make_unique<Animation>(keyframes, false);
        std::shared_ptr<RAPID_model> mesh = meshParser->parse(std::any_cast<std::string>(properties.at("mesh")))[0];
        CelestialBody body(animation, mesh, mass, name);
        result.push_back(body);
    }
    return result;
}
