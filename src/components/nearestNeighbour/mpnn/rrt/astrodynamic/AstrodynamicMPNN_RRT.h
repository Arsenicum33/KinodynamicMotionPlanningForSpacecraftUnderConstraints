//
// Created by arseniy on 11.5.25.
//

#ifndef ASTRODYNAMICMPNN_RRT_H
#define ASTRODYNAMICMPNN_RRT_H
#include "components/nearestNeighbour/mpnn/rrt/AMPNN_RRT.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicMPNN_RRT : public AMPNN_RRT<SpaceshipState, Keyframe>
{
public:
    explicit AstrodynamicMPNN_RRT(int maxNeighbours)
        : AMPNN_RRT<SpaceshipState, Keyframe>(maxNeighbours) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; }

    std::vector<std::shared_ptr<TreeNode<SpaceshipState>>> getNodes() override;;
};




#endif //ASTRODYNAMICMPNN_RRT_H
