//
// Created by arseniy on 21.3.25.
//

#ifndef IDYNAMICSSIMULATOR_H
#define IDYNAMICSSIMULATOR_H
#include "components/IComponent.h"

template <typename StateType, typename ControlInputType>
class IDynamicsSimulator : public IComponent
{
public:
    virtual StateType computeNextState(const StateType& currentState, const ControlInputType& controlInput) = 0;

    ComponentType getType() const override { return ComponentType::DynamicsSimulator; }

};

#endif //IDYNAMICSSIMULATOR_H
