//
// Created by arseniy on 29.4.25.
//

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
