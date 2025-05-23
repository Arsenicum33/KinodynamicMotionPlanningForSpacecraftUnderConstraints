// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "AstrodynamicGNAT_Witness.h"

#include "components/nearestNeighbour/ompl/gnat/sst/AGNAT_SST.h"
#include "utils/PhysicsUtils.h"

void AstrodynamicGNAT_Witness::build()
{
    AGNAT_Witness::build();
    using namespace PhysicsUtils;
    gnat.setDistanceFunction([](const std::shared_ptr<Witness<SpaceshipState>>& witness,
                            const std::shared_ptr<Witness<SpaceshipState>>& query)
    {
        return norm(witness->position - query->position);
    });
}

std::shared_ptr<Witness<SpaceshipState>> AstrodynamicGNAT_Witness::searchedTypeToStoredType(
    const SpaceshipState &state) const
{
    std::shared_ptr<Witness<SpaceshipState>> result = std::make_shared<Witness<SpaceshipState>>(state.translation);
    return result;
}
