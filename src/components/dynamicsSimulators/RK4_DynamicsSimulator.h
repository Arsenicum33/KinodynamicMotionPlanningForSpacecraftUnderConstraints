//
// Created by arseniy on 29.4.25.
//

#ifndef RK4_DYNAMICSSIMULATOR_H
#define RK4_DYNAMICSSIMULATOR_H
#include "IDynamicsSimulator.h"
#include "dto/poses/static/pose/Pose.h"
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

    StateType k2Input = currentState + k1 * 0.5;
    k2Input.rotation.normalize();
    StateType k2 = this->derivator->derive(k2Input, controlInput) * timestep;

    StateType k3Input = currentState + k2 * 0.5;
    k3Input.rotation.normalize();
    StateType k3 = this->derivator->derive(k3Input, controlInput) * timestep;

    StateType k4Input = currentState + k3;
    k4Input.rotation.normalize();
    StateType k4 = this->derivator->derive(k4Input, controlInput) * timestep;

    StateType result = currentState + (k1 + k2 * 2 + k3 * 2 + k4) * (1.0/6.0);
    result.rotation.normalize();
    return result;
}

#endif //RK4_DYNAMICSSIMULATOR_H
