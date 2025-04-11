//
// Created by arseniy on 11.4.25.
//

#ifndef IEXTERNALFORCESCOMPUTER_H
#define IEXTERNALFORCESCOMPUTER_H
#include <components/IComponent.h>

#include "components/physics/interactions/IInteraction.h"

template <typename StateType>
class IExternalForcesComputer : public IComponent
{
public:
    virtual void addInteraction(IInteraction<StateType> interaction) = 0;
    virtual TotalForce computeTotalForce(const StateType& state) = 0;

    ComponentType getType() const override { return ComponentType::ExternalForcesComputer; };
};

#endif //IEXTERNALFORCESCOMPUTER_H
