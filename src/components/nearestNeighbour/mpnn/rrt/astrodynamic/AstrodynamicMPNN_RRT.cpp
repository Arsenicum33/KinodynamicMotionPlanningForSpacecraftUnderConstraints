//
// Created by arseniy on 11.5.25.
//

#include "AstrodynamicMPNN_RRT.h"

std::unique_ptr<IComponent> AstrodynamicMPNN_RRT::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_unique<AstrodynamicMPNN_RRT>(maxNeightbours);
}

std::vector<std::shared_ptr<TreeNode<SpaceshipState>>> AstrodynamicMPNN_RRT::getNodes()
{
    throw std::runtime_error("AstrodynamicMPNN_RRT::getNodes() not implemented");
}
