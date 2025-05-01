//
// Created by arseniy on 30.4.25.
//

#include "AstrodynamicDerivator.h"

#include <dto/poses/static/poseMath/PoseMath.h>

#include "dto/totalAcceleration/TotalAcceleration.h"

SpaceshipState AstrodynamicDerivator::derive(const SpaceshipState &currentState, const BurstControlInput &controlInput)
{
    std::array<double, 3> translationChange = currentState.velocity;

    Eigen::Quaterniond currentOrientation = PoseMath::rotationMatrixToQuaternion(currentState.rotation);
    Eigen::Quaterniond angularVelocityAsPureQuaternion(0, currentState.angularVelocity[0],
        currentState.angularVelocity[1], currentState.angularVelocity[2]);
    Eigen::Quaterniond rotationChange = angularVelocityAsPureQuaternion * currentOrientation;
    rotationChange.coeffs() *= 0.5;

    TotalAcceleration acceleration = physicsSimulator->computeAcceleration(currentState, controlInput);

    std::array<double, 3> velocityChange = acceleration.getLinearAcceleration();
    std::array<double,3> angularVelocityChange = acceleration.getAngularAcceleration();
    double timeChange = 1;
    FuelState fuelStateChange(-fuelSystem->getThrustToFuelFlowRation() *controlInput.getThrust(),
        -fuelSystem->getTorqueToFuelFlowRatio() * PhysicsUtils::norm(controlInput.getTorque()));
    return SpaceshipState(State(translationChange, rotationChange, timeChange, velocityChange,
        angularVelocityChange), fuelStateChange);
}

void AstrodynamicDerivator::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IDerivator<SpaceshipState>::resolveDependencies(config, manager);
    physicsSimulator = std::dynamic_pointer_cast<IPhysicsSimulator<SpaceshipState>>(
        manager->getComponent(ComponentType::PhysicsSimulator));
    fuelSystem = std::dynamic_pointer_cast<IFuelSystem>(
        manager->getComponent(ComponentType::FuelSystem));
}
