//
// Created by arseniy on 11.4.25.
//

#ifndef IPHYSICSSIMULATOR_H
#define IPHYSICSSIMULATOR_H
#include <components/IComponent.h>
#include <dto/controlInputPlan/ControlInputPlan.h>

template <typename StateType, typename ControlInputType>
class IPhysicsSimulator : public IComponent
{
public:
    virtual StateType computeNextState(StateType currentState, const ControlInputPlan<ControlInputType>& inputPlan) = 0;

    ComponentType getType() const override { return ComponentType::PhysicsSimulator; };
};

#endif //IPHYSICSSIMULATOR_H
