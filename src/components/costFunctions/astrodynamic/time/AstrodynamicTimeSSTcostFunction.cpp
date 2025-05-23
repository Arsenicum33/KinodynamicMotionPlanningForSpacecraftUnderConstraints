// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "AstrodynamicTimeSSTcostFunction.h"

double AstrodynamicTimeSSTcostFunction::getCost(std::shared_ptr<SSTnode<SpaceshipState>> parent,
                                                const SpaceshipState &currentState)
{
    return parent->cost + (currentState.time - parent->state.time);
}
