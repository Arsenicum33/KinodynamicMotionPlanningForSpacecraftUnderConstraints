//
// Created by arseniy on 24.10.24.
//

#include "InputParser.h"

#include <dto/EnvSettings.h>
#include <spdlog/spdlog.h>

#include "dto/EnvSettingsRaw.h"
#include "poses/static/PoseMath.h"


InputParser::InputParser(int argc, char *argv[], bool useDefaultParameterValues)
    : envSettings(useDefaultParameterValues ? createDefaultEnvSettings()
                                        : createEnvSettingsFromFile(std::string(argv[1])))
{
    validateFilePath(envSettings.obstaclesFilepath, "Obstacle");
    validateFilePath(envSettings.agentFilepath, "Agent");
}

const EnvSettingsRaw& InputParser::getEnvSettingsRaw()
{
    return envSettings;
}

void InputParser::validateFilePath(const std::string &path, const std::string &fileType) const
{
    if (!std::filesystem::exists(path))
    {
        spdlog::error(fileType + " file not found: " + path);
        throw std::invalid_argument("Invalid filepath");
    }
}

EnvSettingsRaw InputParser::createDefaultEnvSettings()
{
    spdlog::info("Using default settings");
    Pose startPose({-20.0, 0.0, 0.0});
    Pose endPose({20.0, 0.0, 0.0});
    std::string agentFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/cube.obj";
    std::string obstaclesFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/2_walls_cons_2.obj";
    std::vector<std::string> dynamicObjects = {"/home/arseniy/Bachaerlors_thesis/Semester_project/blender/animations/doorCyclic2.fbx",
                                                    "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/animations/movingCube.fbx"};
    ConfigurationSpaceBoundaries boundaries(-30.0, 30.0, -30.0, 30.0, -15.0, 15.0);
    return EnvSettingsRaw(startPose, endPose, boundaries, agentFilepath, obstaclesFilepath, dynamicObjects);
}

EnvSettingsRaw InputParser::createEnvSettingsFromFile(const std::string &filepath)
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
        const std::array<double, 3>& endPosTranslation = parseJsonArrayOfDoubles(root["end_position"]["translation"]);
        const std::array<double, 3>& endPosRotation = parseJsonArrayOfDoubles(root["end_position"]["rotation"]);
        Pose endPose(endPosTranslation, PoseMath::eulerToRotationMatrix(endPosRotation));
        target = endPose;
    }
    catch (const std::exception &e)
    {
        spdlog::warn("Target is dynamic");
        std::string movingTargetAnimationFilepath = root["target_filepath"].asString();
        target = movingTargetAnimationFilepath;
    }



    const std::string& agentFilepath = root["agent_filepath"].asString();
    const std::string& obstacleFilepath = root["obstacles_filepath"].asString();
    std::vector<std::string> dynamicObjectsFilepaths = parseJsonVectorOfStrings(root["dynamic_objects_filepaths"]);
    EnvSettingsRaw settings(startPose, target, boundaries, agentFilepath, obstacleFilepath,dynamicObjectsFilepaths);
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