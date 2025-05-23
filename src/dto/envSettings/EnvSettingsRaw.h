// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
    EnvSettingsRaw(std::shared_ptr<Pose> startPose, const std::variant<Pose, std::string>& target, const ConfigurationSpaceBoundaries& boundaries, const std::string& agentFilepath, const std::string& obstaclesFilepath,
                const std::vector<std::string> &dynamicObjectsFilepaths, const std::string& componentsPresetFilepath) :
        start(startPose), target(target), boundaries(boundaries), agentFilepath(agentFilepath), obstaclesFilepath(obstaclesFilepath),
        dynamicObjectsFilepaths(dynamicObjectsFilepaths), componentsPresetFilepath(componentsPresetFilepath){}
    std::shared_ptr<Pose> start;
    std::variant<Pose, std::string> target;
    ConfigurationSpaceBoundaries boundaries;
    std::string agentFilepath;
    std::string obstaclesFilepath;
    std::vector<std::string> dynamicObjectsFilepaths;
    std::string componentsPresetFilepath;
};
#endif //ENVSETTINGSRAW_H
