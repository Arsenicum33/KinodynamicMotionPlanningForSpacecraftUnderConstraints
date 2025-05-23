// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "KinodynamicTimeSSTcostFunction.h"

double KinodynamicTimeSSTcostFunction::getCost(std::shared_ptr<SSTnode<State>> parent, const State &currentState)
{
        return parent->cost + (currentState.time - parent->state.time);
}
