// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

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
    spdlog::warn("AstrodynamicMPNN_RRT::getNodes() not implemented");
    return std::vector<std::shared_ptr<TreeNode<SpaceshipState>>>();
}
