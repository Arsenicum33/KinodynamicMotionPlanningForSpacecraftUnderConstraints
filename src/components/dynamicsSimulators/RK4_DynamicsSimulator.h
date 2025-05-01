//
// Created by arseniy on 29.4.25.
//

#ifndef RK4_DYNAMICSSIMULATOR_H
#define RK4_DYNAMICSSIMULATOR_H
#include "IDynamicsSimulator.h"

template <typename StateType>
class RK4_DynamicsSimulator : public IDynamicsSimulator<StateType>
{
public:
    StateType integrate(const StateType &currentState, const BurstControlInput &controlInput,
        double timestep) override;
};

template<typename StateType>
StateType RK4_DynamicsSimulator<StateType>::integrate(const StateType &currentState,
    const BurstControlInput &controlInput, double timestep)
{
    StateType k1 = this->derivator->derive(currentState, controlInput) * timestep;
    StateType k2 = this->derivator->derive(currentState + k1*0.5, controlInput) * timestep;
    StateType k3 = this->derivator->derive(currentState + k2*0.5, controlInput) * timestep;
    StateType k4 = this->derivator->derive(currentState + k3, controlInput) * timestep;
    StateType result = currentState + (k1 + k2 * 2 + k3 * 2 + k4) * (1.0/6.0);
    return result;
}

#endif //RK4_DYNAMICSSIMULATOR_H
