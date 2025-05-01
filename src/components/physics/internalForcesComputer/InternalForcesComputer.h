//
// Created by arseniy on 10.4.25.
//

#ifndef INTERNALFORCESCOMPUTER_H
#define INTERNALFORCESCOMPUTER_H
#include "IInternalForcesComputer.h"
#include "components/physics/totalForce/TotalForce.h"
#include "dto/spaceshipModel/SpaceshipModel.h"

template <typename StateType>
class InternalForcesComputer : public IInternalForcesComputer<StateType>
{
public:
    TotalForce computeTotalForce(const StateType& state, const BurstControlInput& controlInput) final;
protected:
    virtual TotalForce computeThrust(const StateType& state, const BurstControlInput& controlInput);
    virtual TotalForce computeTorque(const StateType& state, const BurstControlInput& controlInput);
};

template<typename StateType>
TotalForce InternalForcesComputer<StateType>::computeTotalForce(const StateType &state,
    const BurstControlInput &controlInput)
{
    return computeThrust(state, controlInput) + computeTorque(state, controlInput);
}

template<typename StateType>
TotalForce InternalForcesComputer<StateType>::computeThrust(const StateType &state,
    const BurstControlInput &controlInput)
{
    using namespace PhysicsUtils;
    std::array<double,3> directionVectorGlobal { state.rotation[0][1], state.rotation[1][1], state.rotation[2][1]};
    TotalForce totalForce(directionVectorGlobal * controlInput.getThrust(), std::array<double,3> {0.0,0.0,0.0});
    return totalForce;
}

template<typename StateType>
TotalForce InternalForcesComputer<StateType>::computeTorque(const StateType &state,
    const BurstControlInput &controlInput)
{
    return TotalForce(std::array<double,3> {0.0,0.0,0.0}, controlInput.getTorque());
}


#endif //INTERNALFORCESCOMPUTER_H
