//
// Created by arseniy on 9.5.25.
//

#include "KinodynamicTimeSSTcostFunction.h"

double KinodynamicTimeSSTcostFunction::getCost(std::shared_ptr<SSTnode<State>> parent, const State &currentState)
{
        return parent->cost + (currentState.time - parent->state.time);
}
