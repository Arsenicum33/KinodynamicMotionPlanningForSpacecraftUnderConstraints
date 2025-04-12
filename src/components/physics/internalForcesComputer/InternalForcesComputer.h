//
// Created by arseniy on 10.4.25.
//

#ifndef INTERNALFORCESCOMPUTER_H
#define INTERNALFORCESCOMPUTER_H
#include "IInternalForcesComputer.h"
#include "components/physics/totalForce/TotalForce.h"
#include "dto/spaceshipModel/SpaceshipModel.h"

template <typename StateType, typename ControlInputType>
class InternalForcesComputer : public IInternalForcesComputer<StateType, ControlInputType>
{
public:
    TotalForce computeTotalForce(const StateType& state, const ControlInputType& controlInput) final;
protected:
    virtual TotalForce computeThrust(const StateType& state, const ControlInputType& controlInput);
    virtual TotalForce computeTorque(const StateType& state, const ControlInputType& controlInput);
};

template<typename StateType, typename ControlInputType>
TotalForce InternalForcesComputer<StateType, ControlInputType>::computeTotalForce(const StateType &state,
    const ControlInputType &controlInput)
{
    return computeThrust(state, controlInput) + computeTorque(state, controlInput);
}

template<typename StateType, typename ControlInputType>
TotalForce InternalForcesComputer<StateType, ControlInputType>::computeThrust(const StateType &state,
    const ControlInputType &controlInput)
{
    using namespace PhysicsUtils;
    std::array<double,3> directionVectorGlobal { state.rotation[0][1], state.rotation[1][1], state.rotation[2][1]};
    TotalForce totalForce(directionVectorGlobal * controlInput.getThrust(), std::array<double,3> {0.0,0.0,0.0});
    return totalForce;
}

template<typename StateType, typename ControlInputType>
TotalForce InternalForcesComputer<StateType, ControlInputType>::computeTorque(const StateType &state,
    const ControlInputType &controlInput)
{
    return TotalForce(std::array<double,3> {0.0,0.0,0.0}, controlInput.getTorque());
}


#endif //INTERNALFORCESCOMPUTER_H
