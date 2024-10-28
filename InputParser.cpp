//
// Created by arseniy on 24.10.24.
//

#include "InputParser.h"

#include "poses/PoseMath.h"


InputParser::InputParser(int argc, char *argv[], bool useDefaultParameterValues)
    : envSettings(useDefaultParameterValues ? createDefaultEnvSettings()
                                        : createEnvSettingsFromFile(std::string(argv[1])))
{
    if (useDefaultParameterValues)
    {
        envSettings = createDefaultEnvSettings();
        validateFilePath(envSettings.obstaclesFilepath, "Obstacle");
        validateFilePath(envSettings.agentFilepath, "Agent");
        return;
    }

    if (argc < 2)
        throw std::invalid_argument(
            "Program takes exactly 2 arguments: exec_name, envSettingsTempFilePath");

    std::string filepath = std::string(argv[1]);
    envSettings = createEnvSettingsFromFile(filepath);

    validateFilePath(envSettings.obstaclesFilepath, "Obstacle");
    validateFilePath(envSettings.agentFilepath, "Agent");
}

const EnvSettings& InputParser::getEnvSettings()
{
    return envSettings;
}

void InputParser::validateFilePath(const std::string &path, const std::string &fileType) const
{
    if (!std::filesystem::exists(path))
        throw std::invalid_argument(fileType + " file not found: " + path);
}

EnvSettings InputParser::createDefaultEnvSettings()
{
    Pose startPose({-20.0, 0.0, 0.0});
    Pose endPose({20.0, 0.0, 0.0});
    std::string agentFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/cube.obj";
    std::string obstaclesFilepath = "/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/2_walls_cons.obj";
    ConfigurationSpaceBoundaries boundaries(-30.0, 30.0, -30.0, 30.0, -15.0, 15.0);
    return EnvSettings(startPose, endPose, boundaries, agentFilepath, obstaclesFilepath);
}

EnvSettings InputParser::createEnvSettingsFromFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open config file: " + filepath);
    }

    Json::CharReaderBuilder reader;
    Json::Value root;
    std::string errors;

    if (!parseFromStream(reader, file, &root, &errors))
    {
        throw std::runtime_error("Failed to parse JSON: " + errors);
    }

    auto boundaries = ConfigurationSpaceBoundaries::fromJson(root["boundaries"]);
    const std::array<double, 3>& startPosTranslation = parseJsonArrayOfDoubles(root["start_position"]["translation"]);
    const std::array<double, 3>& startPosRotation = parseJsonArrayOfDoubles(root["start_position"]["rotation"]);
    const std::array<double, 3>& endPosTranslation = parseJsonArrayOfDoubles(root["end_position"]["translation"]);
    const std::array<double, 3>& endPosRotation = parseJsonArrayOfDoubles(root["end_position"]["rotation"]);
    Pose startPose(startPosTranslation, PoseMath::eulerToRotationMatrix(startPosRotation));
    Pose endPose(endPosTranslation, PoseMath::eulerToRotationMatrix(endPosRotation));
    const std::string& agentFilepath = root["agent_filepath"].asString();
    const std::string& obstacleFilepath = root["obstacles_filepath"].asString();
    EnvSettings settings(startPose, endPose, boundaries, agentFilepath, obstacleFilepath);
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