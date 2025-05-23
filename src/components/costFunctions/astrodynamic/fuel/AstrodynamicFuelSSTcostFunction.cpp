// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "AstrodynamicFuelSSTcostFunction.h"

double AstrodynamicFuelSSTcostFunction::getCost(std::shared_ptr<SSTnode<SpaceshipState>> parent,
    const SpaceshipState &currentState)
{
    return parent->cost + (parent->state.getFuel().getMainThrusterFuel() - currentState.getFuel().getMainThrusterFuel()
        +parent->state.getFuel().getRotationThrustersFuel() - currentState.getFuel().getRotationThrustersFuel());
}
