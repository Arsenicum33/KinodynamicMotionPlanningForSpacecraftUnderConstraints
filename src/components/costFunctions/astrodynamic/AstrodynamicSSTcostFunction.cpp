//
// Created by arseniy on 5.5.25.
//

#include "AstrodynamicSSTcostFunction.h"

double AstrodynamicSSTcostFunction::getCost(std::shared_ptr<SSTnode<SpaceshipState>> parent,
    const SpaceshipState &currentState)
{
    return parent->cost + (parent->state.getFuel().getMainThrusterFuel() - currentState.getFuel().getMainThrusterFuel()
        +parent->state.getFuel().getRotationThrustersFuel() - currentState.getFuel().getRotationThrustersFuel());
    //return parent->cost + (currentState.time - parent->state.time);
}
