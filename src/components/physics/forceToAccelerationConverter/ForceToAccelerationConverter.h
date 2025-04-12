//
// Created by arseniy on 11.4.25.
//

#ifndef FORCETOACCELERATIONCONVERTER_H
#define FORCETOACCELERATIONCONVERTER_H
#include "IForceToAccelerationConverter.h"
#include "dto/spaceshipModel/SpaceshipModel.h"

template <typename StateType>
class ForceToAccelerationConverter : public IForceToAccelerationConverter<StateType>
{
public:
    ForceToAccelerationConverter(std::shared_ptr<SpaceshipModel> spaceshipModel) :
        spaceshipModel(spaceshipModel) {}
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv};}

    TotalAcceleration convert(const TotalForce &force, const StateType& state) override;

protected:
    std::array<double, 3> convertForceToLinearAcceleration(std::array<double, 3> force, const StateType& state);
    std::array<double, 3> convertTorqueToAngularAcceleration(std::array<double, 3> torque, const StateType& state);

private:
    std::shared_ptr<SpaceshipModel> spaceshipModel;
};

template<typename StateType>
TotalAcceleration ForceToAccelerationConverter<StateType>::convert(const TotalForce &force, const StateType &state)
{
    return TotalAcceleration(convertForceToLinearAcceleration(force.getForce(), state),
    convertTorqueToAngularAcceleration(force.getTorque(), state));
}

template<typename StateType>
std::array<double, 3> ForceToAccelerationConverter<StateType>::convertForceToLinearAcceleration(
    std::array<double, 3> force, const StateType& state)
{
    using namespace PhysicsUtils;
    return force * (1 / spaceshipModel->getTotalMass(state));
}

template<typename StateType>
std::array<double, 3> ForceToAccelerationConverter<StateType>::convertTorqueToAngularAcceleration(
    std::array<double, 3> torque, const StateType& state)
{
    const Eigen::Matrix3d& inertiaTensor = spaceshipModel->getInertiaTensor(state);
    Eigen::Vector3d angularAcceleration = inertiaTensor.inverse() * Eigen::Vector3d(torque[0], torque[1], torque[2]);
    std::array<double,3> result { angularAcceleration.x(), angularAcceleration.y(), angularAcceleration.z()};
    return result;
}


#endif //FORCETOACCELERATIONCONVERTER_H
