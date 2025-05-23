// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "KinodynamicGNAT_Witness.h"

#include <utils/PhysicsUtils.h>

void KinodynamicGNAT_Witness::build()
{
    AGNAT_Witness::build();
    using namespace PhysicsUtils;
    gnat.setDistanceFunction([](const std::shared_ptr<Witness<State>>& witness,
                            const std::shared_ptr<Witness<State>>& query)
    {
        return norm(witness->position - query->position);
    });
}

std::shared_ptr<Witness<State>> KinodynamicGNAT_Witness::searchedTypeToStoredType(
    const State &state) const
{
    std::shared_ptr<Witness<State>> result = std::make_shared<Witness<State>>(state.translation);
    return result;
}
