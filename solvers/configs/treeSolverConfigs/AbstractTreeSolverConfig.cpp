//
// Created by arseniy on 23.10.24.
//

#include "AbstractTreeSolverConfig.h"

AbstractTreeSolverConfig AbstractTreeSolverConfig::fromJson(const Json::Value &json)
{
    if (!json.isMember("maxIterations") || !json.isMember("goalBias") ||
        !json.isMember("interpolationDistanceThreshold") || !json.isMember("maxStepSize"))
    {
        throw std::invalid_argument("Missing required fields in AbstractTreeSolverConfig");
    }

    return AbstractTreeSolverConfig(
        json["goalBias"].asDouble(),
        json["maxIterations"].asInt(),
        json["maxStepSize"].asDouble(),
        json["interpolationDistanceThreshold"].asDouble(),
        json["interpolationRotationDistanceThreshold"].asDouble(),
        json["rotationScalingFactor"].asDouble()
    );
}
