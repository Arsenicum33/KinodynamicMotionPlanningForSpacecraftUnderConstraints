//
// Created by arseniy on 25.10.24.
//

#ifndef ENVSETTINGS_H
#define ENVSETTINGS_H
#include "ConfigurationSpaceBoundaries.h"
#include "poses/Pose.h"

class EnvSettings
{
public:
    EnvSettings(const Pose& startPose, const Pose& endPose, const ConfigurationSpaceBoundaries& boundaries, const std::string& agentFilepath, const std::string& obstaclesFilepath) :
        startPose(startPose), endPose(endPose), boundaries(boundaries), agentFilepath(agentFilepath), obstaclesFilepath(obstaclesFilepath) {}
    Pose startPose;
    Pose endPose;
    ConfigurationSpaceBoundaries boundaries;
    std::string agentFilepath;
    std::string obstaclesFilepath;
};

#endif //ENVSETTINGS_H
