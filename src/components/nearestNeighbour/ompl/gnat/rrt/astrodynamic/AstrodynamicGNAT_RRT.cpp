//
// Created by arseniy on 11.5.25.
//

#include "AstrodynamicGNAT_RRT.h"

#include <utils/PhysicsUtils.h>

void AstrodynamicGNAT_RRT::build()
{
    AGNAT_RRT::build();
    using namespace PhysicsUtils;
    gnat.setDistanceFunction([&](const std::shared_ptr<TreeNode<SpaceshipState>>& node,
                             const std::shared_ptr<TreeNode<SpaceshipState>>& query) {
    return norm(node->pose.translation - query->pose.translation);
});
}

std::shared_ptr<TreeNode<SpaceshipState>> AstrodynamicGNAT_RRT::searchedTypeToStoredType(
    const Keyframe &keyframe) const
{
    std::shared_ptr<TreeNode<SpaceshipState>> result = std::make_shared<TreeNode<SpaceshipState>>(
        SpaceshipState(State(keyframe, {0.0,0.0,0.0}, {0.0,0.0,0.0}), FuelState(-1.0,-1.0)), nullptr, -1.0);
    return result;
}