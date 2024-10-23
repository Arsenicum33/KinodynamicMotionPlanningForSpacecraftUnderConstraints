//
// Created by arseniy on 23.10.24.
//

#include "AbstractSolverConfig.h"


AbstractSolverConfig AbstractSolverConfig::fromJson(const Json::Value &json)
{
    if (!json.isMember("boundaries"))
    {
        throw std::invalid_argument("Missing required fields in AbstractSolverConfig");
    }

    return AbstractSolverConfig(ConfigurationSpaceBoundaries::fromJson(json["boundaries"]));
}
