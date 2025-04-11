//
// Created by arseniy on 10.4.25.
//

#ifndef EXTERNALFORCESCOMPUTER_H
#define EXTERNALFORCESCOMPUTER_H
#include "IExternalForcesComputer.h"
#include "components/physics/interactions/IInteraction.h"
#include "components/physics/totalForce/TotalForce.h"


template <typename StateType>
class ExternalForcesComputer : public IExternalForcesComputer<StateType>
{
public:
    void addInteraction(IInteraction<StateType> interaction) override { interactions.push_back(interaction); }
    TotalForce computeTotalForce(const StateType& state) override;
private:
    std::vector<IInteraction<StateType>> interactions;
};

template<typename StateType>
TotalForce ExternalForcesComputer<StateType>::computeTotalForce(const StateType &state)
{
    TotalForce totalForce;
    for (const auto& interaction : interactions)
    {
        TotalForce force = interaction.computeTotalForce(state);
        totalForce += force;
    }
    return totalForce;
}


#endif //EXTERNALFORCESCOMPUTER_H
