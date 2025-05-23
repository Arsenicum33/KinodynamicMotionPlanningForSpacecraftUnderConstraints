// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef EULER_DYNAMICSSIMULATOR_H
#define EULER_DYNAMICSSIMULATOR_H
#include "IDynamicsSimulator.h"

template <typename StateType>
class Euler_DynamicsSimulator : public IDynamicsSimulator<StateType>
{
public:
    StateType integrate(const StateType &currentState, const BurstControlInput &controlInput,
        double timestep) override;
};

template<typename StateType>
StateType Euler_DynamicsSimulator<StateType>::integrate(const StateType &currentState,
    const BurstControlInput &controlInput, double timestep)
{
    return currentState + this->derivator->derive(currentState, controlInput) * timestep;
}

#endif //EULER_DYNAMICSSIMULATOR_H
