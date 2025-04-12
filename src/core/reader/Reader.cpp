//
// Created by arseniy on 13.1.25.
//

#include "Reader.h"

#include <spdlog/spdlog.h>
#include <utils/PhysicsUtils.h>

#include "dto/envSettings/EnvSettingsAstro.h"
#include "utils/ScalingUtils.h"


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
    std::shared_ptr<Pose> start = rawSettings->start;
    std::variant<Pose, std::shared_ptr<DynamicObject<RAPID_model>>> target = processTarget(*rawSettings);
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
    scaleEnvSettings(*(envSettings.get()), AU_TO_KM_SCALING_CONSTANT);
    if (this->celestialBodies.empty())
        createCelestialBodies(rawSettings->celestialBodies);
    std::shared_ptr<SpaceshipModel> spaceshipModel = std::make_shared<SpaceshipModel>(rawSettings->spaceshipModel);
    return std::make_unique<EnvSettingsAstro>(*(envSettings.release()), celestialBodies, spaceshipModel);
}

void Reader::createCelestialBodies(std::unordered_map<std::string, std::unordered_map<std::string, std::any>> celestialBodies)
{
    for (const auto& [name, properties] : celestialBodies)
    {
        std::vector<double> times = std::any_cast<std::vector<double>>(properties.at("times"));
        std::vector<std::array<double, 3>> positions = std::any_cast<std::vector<std::array<double, 3>>>(properties.at("positions"));
        long double mass = std::any_cast<long double>(properties.at("mass"));
        double radius = std::any_cast<double>(properties.at("radius"));
        std::vector<Keyframe> keyframes;
        for (int i=0;i<times.size();i++)
        {
            std::array<double, 3> positionsScaled = PhysicsUtils::operator*(positions[i], AU_TO_KM_SCALING_CONSTANT);
            Keyframe keyframe(positionsScaled, times[i]);
            keyframes.push_back(keyframe);
        }
        std::shared_ptr<Animation> animation = std::make_unique<Animation>(keyframes, false);
        std::shared_ptr<RAPID_model> mesh = meshParser->parse(std::any_cast<std::string>(properties.at("mesh")))[0];
        CelestialBody body(animation, mesh, mass, radius, name);
        this->celestialBodies.push_back(body);
    }
}

void Reader::scaleEnvSettings(EnvSettings &envSettings, double scale)
{
    envSettings.boundaries.xMin *= scale;
    envSettings.boundaries.xMax *= scale;
    envSettings.boundaries.yMin *= scale;
    envSettings.boundaries.yMax *= scale;
    envSettings.boundaries.zMin *= scale;
    envSettings.boundaries.zMax *= scale;

    envSettings.start->translation = PhysicsUtils::operator*(envSettings.start->translation, scale);
    //TODO potentially scale dynamic objects
}


std::variant<Pose, std::shared_ptr<DynamicObject<RAPID_model>>> Reader::processTarget(const EnvSettingsRaw& rawSettings)
{
    if (std::holds_alternative<Pose>(rawSettings.target))
        return std::get<Pose>(rawSettings.target);
    if (!std::holds_alternative<std::string>(rawSettings.target))
    {
        spdlog::error("Target is of unknown type");
        throw std::runtime_error("Target is of unknown type");
    }
    std::string targetString = std::get<std::string>(rawSettings.target);
    if (targetString.ends_with(".fbx"))
        return animationParser->parse(targetString);

    const EnvSettingsAstroRaw& rawSettingsAstro = dynamic_cast<const EnvSettingsAstroRaw&>(rawSettings);
    if (this->celestialBodies.empty())
        createCelestialBodies(rawSettingsAstro.celestialBodies);
    for (auto& body : celestialBodies)
    {
        if (body.getName() == targetString)
            return std::make_shared<CelestialBody>(body);
    }
    spdlog::error("Failed to parse target");
    throw std::runtime_error("Failed to parse target");
}
