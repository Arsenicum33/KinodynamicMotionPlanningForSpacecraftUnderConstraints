// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef STATICMPNN_RRT_H
#define STATICMPNN_RRT_H
#include "components/nearestNeighbour/mpnn/rrt/AMPNN_RRT.h"


class StaticMPNN_RRT : public AMPNN_RRT<Pose, Pose>
{
public:
    explicit StaticMPNN_RRT(int maxNeighbours)
        : AMPNN_RRT<Pose, Pose>(maxNeighbours) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    std::vector<std::shared_ptr<TreeNode<Pose>>> getNodes() override;;
};



#endif //STATICMPNN_RRT_H
