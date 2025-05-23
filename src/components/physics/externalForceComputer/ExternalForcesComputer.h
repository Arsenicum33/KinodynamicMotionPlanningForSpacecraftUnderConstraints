// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef EXTERNALFORCESCOMPUTER_H
#define EXTERNALFORCESCOMPUTER_H
#include "IExternalForcesComputer.h"
#include "components/physics/interactions/IInteraction.h"
#include "components/physics/totalForce/TotalForce.h"


template <typename StateType>
class ExternalForcesComputer : public IExternalForcesComputer<StateType>
{
public:
    void addInteraction(std::shared_ptr<IInteraction<StateType>> interaction) override { interactions.push_back(interaction); }
    TotalForce computeTotalForce(const StateType& state) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    std::vector<std::shared_ptr<IInteraction<StateType>>> interactions;
};

template<typename StateType>
TotalForce ExternalForcesComputer<StateType>::computeTotalForce(const StateType &state)
{
    TotalForce totalForce;
    for (auto interaction : interactions)
    {
        TotalForce force = interaction->computeTotalForce(state);
        totalForce += force;
    }
    return totalForce;
}

template<typename StateType>
void ExternalForcesComputer<StateType>::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IExternalForcesComputer<StateType>::resolveDependencies(config, manager);
    auto interaction = std::dynamic_pointer_cast<IInteraction<StateType>>(manager->getComponent(ComponentType::Interaction));
    addInteraction(interaction); //TODO make it accept several interactions
}


#endif //EXTERNALFORCESCOMPUTER_H
