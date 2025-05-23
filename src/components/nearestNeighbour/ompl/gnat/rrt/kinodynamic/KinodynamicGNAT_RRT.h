// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef KINODYNAMICGNAT_RRT_H
#define KINODYNAMICGNAT_RRT_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/nearestNeighbour/ompl/gnat/rrt/AGNAT_RRT.h"


class KinodynamicGNAT_RRT : public AGNAT_RRT<State, Keyframe>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<KinodynamicGNAT_RRT>();
    };
    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::KinodynamicEnv};}

    void build() override;

protected:
    std::shared_ptr<TreeNode<State>> searchedTypeToStoredType(const Keyframe &state) const override;
};




#endif //KINODYNAMICGNAT_RRT_H
