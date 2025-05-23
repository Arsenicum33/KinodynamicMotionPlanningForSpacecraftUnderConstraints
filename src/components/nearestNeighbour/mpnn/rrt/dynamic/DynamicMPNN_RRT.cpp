// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "DynamicMPNN_RRT.h"

std::unique_ptr<IComponent> DynamicMPNN_RRT::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_unique<DynamicMPNN_RRT>(maxNeightbours);
}

std::vector<std::shared_ptr<TreeNode<Keyframe>>> DynamicMPNN_RRT::getNodes()
{
    spdlog::warn("DynamicMPNN_RRT::getNodes() not implemented");
    return std::vector<std::shared_ptr<TreeNode<Keyframe>>>();
}
