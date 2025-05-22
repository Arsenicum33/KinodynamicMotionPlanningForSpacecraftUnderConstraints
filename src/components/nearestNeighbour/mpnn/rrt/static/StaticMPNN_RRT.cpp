//
// Created by arseniy on 21.5.25.
//

#include "StaticMPNN_RRT.h"

std::unique_ptr<IComponent> StaticMPNN_RRT::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_unique<StaticMPNN_RRT>(maxNeightbours);
}

std::vector<std::shared_ptr<TreeNode<Pose>>> StaticMPNN_RRT::getNodes()
{
    spdlog::warn("StaticMPNN_RRT::getNodes() not implemented");
    return std::vector<std::shared_ptr<TreeNode<Pose>>>();
}
