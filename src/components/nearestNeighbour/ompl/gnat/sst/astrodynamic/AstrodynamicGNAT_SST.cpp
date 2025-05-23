// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "AstrodynamicGNAT_SST.h"

#include <utils/PhysicsUtils.h>

void AstrodynamicGNAT_SST::build()
{
    AGNAT_SST::build();
    using namespace PhysicsUtils;
    gnat.setDistanceFunction([&](const std::shared_ptr<SSTnode<SpaceshipState>>& node,
                             const std::shared_ptr<SSTnode<SpaceshipState>>& query) {
    return norm(node->state.translation - query->state.translation);
});
}

std::shared_ptr<SSTnode<SpaceshipState>> AstrodynamicGNAT_SST::searchedTypeToStoredType(
    const SpaceshipState &state) const
{
    std::shared_ptr<SSTnode<SpaceshipState>> result = std::make_shared<SSTnode<SpaceshipState>>(state, -1.0);
    return result;
}
