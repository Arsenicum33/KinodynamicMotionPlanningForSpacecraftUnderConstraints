//
// Created by arseniy on 10.4.25.
//

#ifndef INTERNALFORCESCOMPUTER_H
#define INTERNALFORCESCOMPUTER_H
#include "IInternalForcesComputer.h"
#include "components/physics/totalForce/TotalForce.h"
#include "dto/spaceshipModel/SpaceshipModel.h"
#include "dto/poses/static/poseMath/PoseMath.h"

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

    Eigen::Quaterniond bodyFixedFrameThrustVectorAsPureQuat(0, 0, controlInput.getThrust(), 0);
    Eigen::Quaterniond inertialFrameThrustVector = state.rotation * bodyFixedFrameThrustVectorAsPureQuat * state.rotation.conjugate();
    TotalForce totalForce(std::array<double,3>{inertialFrameThrustVector.x(), inertialFrameThrustVector.y(), inertialFrameThrustVector.z()},
        std::array<double,3> {0.0,0.0,0.0});

    //RotationMatrix matrix = PoseMath::quaternionToRotationMatrix(state.rotation);
    //std::array<double,3> directionVectorGlobal { matrix.data[0][1], matrix.data[1][1], matrix.data[2][1]};
    //TotalForce totalForce1(directionVectorGlobal * controlInput.getThrust(), std::array<double,3> {0.0,0.0,0.0});

    return totalForce;
}

template<typename StateType>
TotalForce InternalForcesComputer<StateType>::computeTorque(const StateType &state,
    const BurstControlInput &controlInput)
{
    return TotalForce(std::array<double,3> {0.0,0.0,0.0}, controlInput.getTorque());
}


#endif //INTERNALFORCESCOMPUTER_H
