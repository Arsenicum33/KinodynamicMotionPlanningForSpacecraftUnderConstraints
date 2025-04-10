//
// Created by arseniy on 10.4.25.
//

#ifndef EXTERNALFORCESCOMPUTER_H
#define EXTERNALFORCESCOMPUTER_H
#include "components/physics/interactions/IInteraction.h"
#include "components/physics/totalForce/TotalForce.h"


template <typename StateType>
class ExternalForcesComputer
{
public:
    virtual ~ExternalForcesComputer() = default;
    void addInteraction(IInteraction<StateType> interaction) { interactions.push_back(interaction); }
    virtual TotalForce computeTotalForce(const StateType& state);
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
