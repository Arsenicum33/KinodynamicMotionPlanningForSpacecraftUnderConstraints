// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "ConfigurationSpaceBoundaries.h"

ConfigurationSpaceBoundaries ConfigurationSpaceBoundaries::fromJson(const Json::Value& json)
{
    if (!json.isMember("xMin") || !json.isMember("xMax") ||
            !json.isMember("yMin") || !json.isMember("yMax") ||
            !json.isMember("zMin") || !json.isMember("zMax"))
    {
        throw std::invalid_argument("Missing boundaries fields in configuration");
    }

    return ConfigurationSpaceBoundaries(
        json["xMin"].asDouble(),
        json["xMax"].asDouble(),
        json["yMin"].asDouble(),
        json["yMax"].asDouble(),
        json["zMin"].asDouble(),
        json["zMax"].asDouble()
    );
}

ConfigurationSpaceBoundaries::ConfigurationSpaceBoundaries(double xMin, double xMax, double yMin, double yMax,
                                                           double zMin, double zMax, double yaw_min, double yaw_max, double pitch_min, double pitch_max, double roll_min,
                                                           double roll_max) : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), zMin(zMin), zMax(zMax), yaw_min(yaw_min), yaw_max(yaw_max),
                                                                              pitch_min(pitch_min), pitch_max(pitch_max), roll_min(roll_min), roll_max(roll_max){}
