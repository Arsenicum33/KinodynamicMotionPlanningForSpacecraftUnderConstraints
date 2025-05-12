//
// Created by arseniy on 11.5.25.
//

#include "KinodynamicGNAT_RRT.h"

#include <utils/PhysicsUtils.h>

void KinodynamicGNAT_RRT::build()
{
    AGNAT_RRT::build();
    using namespace PhysicsUtils;
    gnat.setDistanceFunction([&](const std::shared_ptr<TreeNode<State>>& node,
                             const std::shared_ptr<TreeNode<State>>& query) {
    return norm(node->pose.translation - query->pose.translation);
    });
}

std::shared_ptr<TreeNode<State>> KinodynamicGNAT_RRT::searchedTypeToStoredType(
    const Keyframe &keyframe) const
{
    std::shared_ptr<TreeNode<State>> result = std::make_shared<TreeNode<State>>(State(keyframe, {0.0,0.0,0.0}, {0.0,0.0,0.0}), nullptr, -1.0);
    return result;
}
