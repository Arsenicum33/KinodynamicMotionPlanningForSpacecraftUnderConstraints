// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "KinodynamicGNAT_SST.h"

#include <utils/PhysicsUtils.h>

void KinodynamicGNAT_SST::build()
{
    AGNAT_SST::build();
    using namespace PhysicsUtils;
    gnat.setDistanceFunction([&](const std::shared_ptr<SSTnode<State>>& node,
                             const std::shared_ptr<SSTnode<State>>& query) {
    return norm(node->state.translation - query->state.translation);
    });
}

std::shared_ptr<SSTnode<State>> KinodynamicGNAT_SST::searchedTypeToStoredType(
    const State &state) const
{
    std::shared_ptr<SSTnode<State>> result = std::make_shared<SSTnode<State>>(state, -1.0);
    return result;
}
