//
// Created by arseniy on 24.10.24.
//

#include "InputParser.h"

#include <iostream>
#include <dto/configurationSpaceBoundaries/ConfigurationSpaceBoundaries.h>
#include <dto/poses/static/poseMath/PoseMath.h>
#include <spdlog/spdlog.h>

#include "dto/envSettings/EnvSettingsAstro.h"
#include "dto/envSettings/EnvSettingsRaw.h"


InputParser::InputParser(int argc, char *argv[], bool useDefaultParameterValues)
    : envSettings(useDefaultParameterValues ? std::move(createDefaultEnvSettings())
                                        : std::move(createEnvSettingsFromFile(std::string(argv[1]))))
{
    validateFilePath(envSettings->obstaclesFilepath, "Obstacle");
    validateFilePath(envSettings->agentFilepath, "Agent");
}

std::unique_ptr<EnvSettingsRaw> InputParser::getEnvSettingsRaw()
{
    if (!envSettings)
        throw std::runtime_error("Env settings not set");
    return std::move(envSettings);
}

void InputParser::validateFilePath(const std::string &path, const std::string &fileType) const
{
    if (!std::filesystem::exists(path) && path!= "")
    {
        spdlog::error(fileType + " file not found: " + path);
        throw std::invalid_argument("Invalid filepath");
    }
}

std::unique_ptr<EnvSettingsRaw>  InputParser::createDefaultEnvSettings()
{
    spdlog::info("Choose settins type (1 - static, 2 - dynamic, 3 - moving target, 4 - kinodynamic, 5 - astrodynamic");
    int envType = 0;
    std::cin >> envType;
    switch (envType)
    {
        case 1: return createStaticEnvSettings();
        case 2: return createDynamicEnvSettings();
        case 3: return createMovingTargetEnvSettings();
        case 4: return createKinodynamicEnvSettings();
        case 5: return createAstrodynamicEnvSettings();
    }
    spdlog::error("Unknown env type input");
    throw std::invalid_argument("Unknown env type");
}

std::unique_ptr<EnvSettingsRaw>  InputParser::createStaticEnvSettings()
{
    Pose startPose({-20.0, 0.0, 0.0});
    Pose endPose({20.0, 0.0, 0.0});
    std::string agentFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/cube.obj";
    std::string obstaclesFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/2_walls_cons_2.obj";
    std::vector<std::string> dynamicObjects = {};
    ConfigurationSpaceBoundaries boundaries(-30.0, 30.0, -30.0, 30.0, -15.0, 15.0);
    std::string componentsPresetFilename = "componentsStatic.json";
    return std::make_unique<EnvSettingsRaw>(startPose, endPose, boundaries, agentFilepath, obstaclesFilepath, dynamicObjects,componentsPresetFilename);
}

std::unique_ptr<EnvSettingsRaw>  InputParser::createDynamicEnvSettings()
{
    Pose startPose({-20.0, 0.0, 0.0});
    Pose endPose({20.0, 0.0, 0.0});
    std::string agentFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/cube.obj";
    std::string obstaclesFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/2_walls_cons_2.obj";
    std::vector<std::string> dynamicObjects = {"/home/arseniy/Bachaerlors_thesis/Semester_project/blender/animations/movingCube.fbx",
                                                "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/animations/doorCyclic2.fbx"};
    ConfigurationSpaceBoundaries boundaries(-30.0, 30.0, -30.0, 30.0, -15.0, 15.0);
    std::string componentsPresetFilename = "componentsDynamic.json";
    return std::make_unique<EnvSettingsRaw>(startPose, endPose, boundaries, agentFilepath, obstaclesFilepath, dynamicObjects,componentsPresetFilename);
}

std::unique_ptr<EnvSettingsRaw>  InputParser::createMovingTargetEnvSettings()
{
    Pose startPose({0.0, 0.0, 0.0});
    std::string target = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/animations/fuckingSphere1.fbx";
    std::string agentFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/cube.obj";
    std::string obstaclesFilepath = "";
    std::vector<std::string> dynamicObjects = {"/home/arseniy/Bachaerlors_thesis/Semester_project/blender/animations/doorCyclic2.fbx"};
    ConfigurationSpaceBoundaries boundaries(-20.0, 20.0, -20.0, 20.0, -10.0, 10.0);
    std::string componentsPresetFilename = "componentsMovingTarget.json";
    return std::make_unique<EnvSettingsRaw>(startPose, target, boundaries, agentFilepath, obstaclesFilepath, dynamicObjects, componentsPresetFilename);
}

std::unique_ptr<EnvSettingsRaw>  InputParser::createKinodynamicEnvSettings()
{
    Pose startPose({0.0, -100.0, 0.0});
    std::string target = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/animations/target1.fbx";
    std::string agentFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/rocketBig.obj";
    std::string obstaclesFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/scattered.obj";
    std::vector<std::string> dynamicObjects = {};
    ConfigurationSpaceBoundaries boundaries(-50.0, 50.0, -120.0, 120.0, -50.0, 50.0);
    std::string componentsPresetFilename = "componentsKinodynamic.json";
    return std::make_unique<EnvSettingsRaw>(startPose, target, boundaries, agentFilepath, obstaclesFilepath, dynamicObjects, componentsPresetFilename);
}

std::unique_ptr<EnvSettingsAstroRaw> InputParser::createAstrodynamicEnvSettings()
{
    Pose startPose({0.0, 0.0, 0.0}, std::array<double, 3>{0.0, 0.0, 180});
    std::string target = "earth";
    std::string agentFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/rocketBig.obj";
    std::string obstaclesFilepath = "";
    std::vector<std::string> dynamicObjects = {};
    ConfigurationSpaceBoundaries boundaries(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
    std::string componentsPresetFilename = "componentsAstrodynamic.json";

    EnvSettingsRaw settings(startPose, target, boundaries, agentFilepath, obstaclesFilepath, dynamicObjects, componentsPresetFilename);
    auto celestialBodies = parseCelestialBodiesFromFile("../celestialBodies.json");
    return std::make_unique<EnvSettingsAstroRaw>(settings, celestialBodies);
}


std::unique_ptr<EnvSettingsRaw>  InputParser::createEnvSettingsFromFile(const std::string &filepath)
{

    std::ifstream file(filepath);
    if (!file.is_open())
    {
        spdlog::error("Config file not found. Path: {}", filepath);
        throw std::runtime_error("Config file not found");
    }

    Json::CharReaderBuilder reader;
    Json::Value root;
    std::string errors;

    if (!parseFromStream(reader, file, &root, &errors))
    {
        spdlog::error("Failed to create EnvSettings. File parsing error: {}", errors);
        throw std::runtime_error("Failed to parse JSON");
    }

    auto boundaries = ConfigurationSpaceBoundaries::fromJson(root["boundaries"]);

    const std::array<double, 3>& startPosTranslation = parseJsonArrayOfDoubles(root["start_position"]["translation"]);
    const std::array<double, 3>& startPosRotation = parseJsonArrayOfDoubles(root["start_position"]["rotation"]);
    Pose startPose(startPosTranslation, PoseMath::eulerToRotationMatrix(startPosRotation));

    std::variant<Pose, std::string> target;
    try
    {
        const std::array<double, 3>& endPosTranslation = parseJsonArrayOfDoubles(root["target"]["translation"]);
        const std::array<double, 3>& endPosRotation = parseJsonArrayOfDoubles(root["target"]["rotation"]);
        Pose endPose(endPosTranslation, PoseMath::eulerToRotationMatrix(endPosRotation));
        target = endPose;
    }
    catch (const std::exception &e)
    {
        spdlog::warn("Target is dynamic");
        target = root["target"].asString();
    }

    const std::string& agentFilepath = root["agent_filepath"].asString();
    const std::string& obstacleFilepath = root["obstacles_filepath"].asString();
    const std::string& componentsPresetFilename = root["components_preset"].asString();
    std::vector<std::string> dynamicObjectsFilepaths = parseJsonVectorOfStrings(root["dynamic_objects_filepaths"]);

    std::unique_ptr<EnvSettingsRaw> settings = std::make_unique<EnvSettingsRaw>(startPose, target, boundaries,
        agentFilepath, obstacleFilepath,dynamicObjectsFilepaths, componentsPresetFilename);

    const std::string& envType = root["env_type"].asString();
    if (envType == "astrodynamic")
    {
        const auto& celestialBodies = parseCelestialBodies(root["celestial_bodies"]);
        double timeScale = root["time_scale"].asDouble();
        double distanceScale = root["distance_scale"].asDouble();
        std::unique_ptr<EnvSettingsAstroRaw> envSettingsAstro = std::make_unique<EnvSettingsAstroRaw>(*(settings.get()), celestialBodies);
        return envSettingsAstro;
    }
    return settings;
}

std::array<double, 3> InputParser::parseJsonArrayOfDoubles(const Json::Value& json)
{
    int it = 0;
    std::array<double, 3> result;
    for (const auto& val : json)
    {
        result[it] = val.asDouble();
        it++;
    }
    return result;
}

std::vector<std::string> InputParser::parseJsonVectorOfStrings(const Json::Value& json)
{
    std::vector<std::string> result;
    for (const auto& val : json)
    {
        result.push_back(val.asString());
    }
    return result;
}

std::unordered_map<std::string, std::unordered_map<std::string, std::any>> InputParser::parseCelestialBodiesFromFile(const std::string& filepath)
{
    std::ifstream file(filepath);
    Json::CharReaderBuilder reader;
    Json::Value json;
    std::string errors;
    if (!Json::parseFromStream(reader, file, &json, &errors))
    {
        throw std::runtime_error("Failed to parse JSON: " + errors);
    }
    return parseCelestialBodies(json);
}

std::unordered_map<std::string, std::unordered_map<std::string, std::any>>  InputParser::parseCelestialBodies(const Json::Value& json)
{
    std::unordered_map<std::string, std::unordered_map<std::string, std::any>> result;
    for (const auto& body : json.getMemberNames())
    {
        const Json::Value& bodyData = json[body];
        std::unordered_map<std::string, std::any> properties;
        properties["mass"] = static_cast<long double>(bodyData["mass"].asDouble()); //TODO improve precision by converting to string
        std::vector<std::array<double, 3>> positions;
        for (const auto& position : std::any_cast<Json::Value>(bodyData["positions"]))
        {
            std::array<double, 3> pos = parseJsonArrayOfDoubles(position);
            positions.push_back(pos);
        }
        properties["positions"] = positions;
        std::vector<double> times;
        for (auto time : std::any_cast<Json::Value>(bodyData["times"]))
        {
            times.push_back(time.asDouble());
        }
        properties["times"] = times;
        properties["mesh"] = bodyData["mesh"].asString();
        result[body] = properties;
    }
    return result;
}