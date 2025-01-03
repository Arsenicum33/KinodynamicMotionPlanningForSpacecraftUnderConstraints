//
// Created by arseniy on 25.10.24.
//

#ifndef ENVSETTINGS_H
#define ENVSETTINGS_H
#include "ConfigurationSpaceBoundaries.h"
#include "poses/static/Pose.h"

class EnvSettings
{
public:
    EnvSettings(const Pose& startPose, const Pose& endPose, const ConfigurationSpaceBoundaries& boundaries, const std::string& agentFilepath, const std::string& obstaclesFilepath,
                const std::vector<std::string> &dynamicObjectsFilepaths = std::vector<std::string>()) :
        startPose(startPose), endPose(endPose), boundaries(boundaries), agentFilepath(agentFilepath), obstaclesFilepath(obstaclesFilepath),
        dynamicObjectsFilepaths(dynamicObjectsFilepaths){}
    Pose startPose;
    Pose endPose;
    ConfigurationSpaceBoundaries boundaries;
    std::string agentFilepath;
    std::string obstaclesFilepath;
    std::vector<std::string> dynamicObjectsFilepaths;
};

#endif //ENVSETTINGS_H
