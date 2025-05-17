//
// Created by arseniy on 11.5.25.
//

#ifndef KINODYNAMICMPNN_RRT_H
#define KINODYNAMICMPNN_RRT_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/nearestNeighbour/mpnn/rrt/AMPNN_RRT.h"


class KinodynamicMPNN_RRT : public AMPNN_RRT<State, Keyframe>
{
public:
    explicit KinodynamicMPNN_RRT(int maxNeighbours)
        : AMPNN_RRT<State, Keyframe>(maxNeighbours) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv}; }

    std::vector<std::shared_ptr<TreeNode<State>>> getNodes() override;;
};




#endif //KINODYNAMICMPNN_RRT_H
