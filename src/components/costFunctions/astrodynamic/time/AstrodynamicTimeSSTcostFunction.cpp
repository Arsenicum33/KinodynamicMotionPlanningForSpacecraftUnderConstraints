//
// Created by arseniy on 5.5.25.
//

#include "AstrodynamicTimeSSTcostFunction.h"

double AstrodynamicTimeSSTcostFunction::getCost(std::shared_ptr<SSTnode<SpaceshipState>> parent,
                                                const SpaceshipState &currentState)
{
    return parent->cost + (currentState.time - parent->state.time);
}
