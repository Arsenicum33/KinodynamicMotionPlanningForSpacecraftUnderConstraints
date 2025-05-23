// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef DYNAMICMPNN_RRT_H
#define DYNAMICMPNN_RRT_H
#include "components/nearestNeighbour/mpnn/rrt/AMPNN_RRT.h"


class DynamicMPNN_RRT : public AMPNN_RRT<Keyframe, Keyframe>
{
public:
    explicit DynamicMPNN_RRT(int maxNeighbours)
        : AMPNN_RRT<Keyframe, Keyframe>(maxNeighbours) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv}; }

    std::vector<std::shared_ptr<TreeNode<Keyframe>>> getNodes() override;
};


#endif //DYNAMICMPNN_RRT_H
