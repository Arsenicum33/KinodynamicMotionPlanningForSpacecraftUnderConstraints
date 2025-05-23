//
// Created by arseniy on 11.4.25.
//

#ifndef FORCETOACCELERATIONCONVERTER_H
#define FORCETOACCELERATIONCONVERTER_H
#include "IForceToAccelerationConverter.h"

template <typename StateType>
class ForceToAccelerationConverter : public IForceToAccelerationConverter<StateType>
{
public:



    TotalAcceleration convert(const TotalForce &force, const StateType& state) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    std::array<double, 3> convertForceToLinearAcceleration(std::array<double, 3> force, const StateType& state);
    std::array<double, 3> convertTorqueToAngularAcceleration(std::array<double, 3> torque, const StateType& state);


private:
    std::shared_ptr<IAgentModel<StateType>> spacecraftModel;
};

template<typename StateType>
TotalAcceleration ForceToAccelerationConverter<StateType>::convert(const TotalForce &force, const StateType &state)
{
    return TotalAcceleration(convertForceToLinearAcceleration(force.getForce(), state),
    convertTorqueToAngularAcceleration(force.getTorque(), state));
}

template<typename StateType>
void ForceToAccelerationConverter<StateType>::resolveDependencies(const ComponentConfig &config,
    ComponentManager *manager)
{
    IForceToAccelerationConverter<StateType>::resolveDependencies(config, manager);
    spacecraftModel = std::dynamic_pointer_cast<IAgentModel<StateType>>(manager->getComponent(ComponentType::AgentModel));
}

template<typename StateType>
std::array<double, 3> ForceToAccelerationConverter<StateType>::convertForceToLinearAcceleration(
    std::array<double, 3> force, const StateType& state)
{
    using namespace PhysicsUtils;
    return force * (1 / spacecraftModel->getTotalMass(state));
}

template<typename StateType>
std::array<double, 3> ForceToAccelerationConverter<StateType>::convertTorqueToAngularAcceleration(
    std::array<double, 3> torque, const StateType& state)
{
    const Eigen::Matrix3d& inertiaTensor = spacecraftModel->getInertiaTensor(state);
    Eigen::Vector3d angularVelocity(state.angularVelocity[0], state.angularVelocity[1], state.angularVelocity[2]);
    Eigen::Vector3d inertiaTensorTimesAngularVelocity = inertiaTensor * angularVelocity;
    Eigen::Vector3d torqueAsEigenVector(torque[0], torque[1], torque[2]);
    Eigen::Vector3d angularAcceleration = inertiaTensor.inverse() * (
        torqueAsEigenVector - angularVelocity.cross(inertiaTensorTimesAngularVelocity));
    std::array<double,3> result { angularAcceleration.x(), angularAcceleration.y(), angularAcceleration.z()};
    return result;
}


#endif //FORCETOACCELERATIONCONVERTER_H
