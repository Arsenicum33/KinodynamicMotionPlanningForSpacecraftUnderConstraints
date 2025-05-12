//
// Created by arseniy on 11.5.25.
//

#include "KinodynamicMPNN_RRT.h"

std::unique_ptr<IComponent> KinodynamicMPNN_RRT::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_unique<KinodynamicMPNN_RRT>(maxNeightbours);
}
