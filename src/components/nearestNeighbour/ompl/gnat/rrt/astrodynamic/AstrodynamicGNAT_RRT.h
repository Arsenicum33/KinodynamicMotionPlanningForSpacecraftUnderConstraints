// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ASTRODYNAMICGNAT_RRT_H
#define ASTRODYNAMICGNAT_RRT_H
#include "components/nearestNeighbour/ompl/gnat/rrt/AGNAT_RRT.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicGNAT_RRT : public AGNAT_RRT<SpaceshipState, Keyframe>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<AstrodynamicGNAT_RRT>();
    };
    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::AstrodynamicEnv};}

    void build() override;

protected:
    std::shared_ptr<TreeNode<SpaceshipState>> searchedTypeToStoredType(const Keyframe &state) const override;
};




#endif //ASTRODYNAMICGNAT_RRT_H
