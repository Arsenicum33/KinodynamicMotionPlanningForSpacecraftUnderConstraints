//
// Created by arseniy on 10.4.25.
//

#ifndef IINTERACTION_H
#define IINTERACTION_H
#include <components/IComponent.h>

#include "components/physics/totalForce/TotalForce.h"

template <typename StateType>
class IInteraction : public IComponent
{
public:
    virtual TotalForce computeTotalForce(const StateType& state) = 0;

    ComponentType getType() const override { return ComponentType::Interaction;}
};

#endif //IINTERACTION_H
