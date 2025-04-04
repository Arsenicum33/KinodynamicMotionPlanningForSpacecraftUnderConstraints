//
// Created by arseniy on 7.3.25.
//

#ifndef ENVSETTINGSRAW_H
#define ENVSETTINGSRAW_H
#include <string>
#include <variant>
#include <dto/configurationSpaceBoundaries/ConfigurationSpaceBoundaries.h>
#include <dto/poses/static/pose/Pose.h>


class EnvSettingsRaw
{
public:
    virtual ~EnvSettingsRaw() = default;
    EnvSettingsRaw(const Pose& startPose, const std::variant<Pose, std::string>& target, const ConfigurationSpaceBoundaries& boundaries, const std::string& agentFilepath, const std::string& obstaclesFilepath,
                const std::vector<std::string> &dynamicObjectsFilepaths, const std::string& componentsPresetFilename) :
        startPose(startPose), target(target), boundaries(boundaries), agentFilepath(agentFilepath), obstaclesFilepath(obstaclesFilepath),
        dynamicObjectsFilepaths(dynamicObjectsFilepaths), componentsPresetFilename(componentsPresetFilename){}
    Pose startPose;
    std::variant<Pose, std::string> target;
    ConfigurationSpaceBoundaries boundaries;
    std::string agentFilepath;
    std::string obstaclesFilepath;
    std::vector<std::string> dynamicObjectsFilepaths;
    std::string componentsPresetFilename;
};
#endif //ENVSETTINGSRAW_H
