//
// Created by arseniy on 9.5.25.
//

#include "AstrodynamicFuelSSTcostFunction.h"

double AstrodynamicFuelSSTcostFunction::getCost(std::shared_ptr<SSTnode<SpaceshipState>> parent,
    const SpaceshipState &currentState)
{
    return parent->cost + (parent->state.getFuel().getMainThrusterFuel() - currentState.getFuel().getMainThrusterFuel()
        +parent->state.getFuel().getRotationThrustersFuel() - currentState.getFuel().getRotationThrustersFuel());
}
