// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "KinodynamicDerivator.h"

State KinodynamicDerivator::derive(const State &currentState, const BurstControlInput &controlInput)
{
    std::array<double, 3> translationChange = currentState.velocity;

    const Eigen::Quaterniond& currentOrientation = currentState.rotation;
    Eigen::Quaterniond angularVelocityAsPureQuaternion(0, currentState.angularVelocity[0],
        currentState.angularVelocity[1], currentState.angularVelocity[2]);
    Eigen::Quaterniond rotationChange = angularVelocityAsPureQuaternion * currentOrientation;
    rotationChange.coeffs() *= 0.5;

    TotalAcceleration acceleration = physicsSimulator->computeAcceleration(currentState, controlInput);

    std::array<double, 3> velocityChange = acceleration.getLinearAcceleration();
    std::array<double,3> angularVelocityChange = acceleration.getAngularAcceleration();
    double timeChange = 1;
    State result(translationChange, rotationChange, timeChange, velocityChange,
        angularVelocityChange);
    return result;
}

void KinodynamicDerivator::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IDerivator<State>::resolveDependencies(config, manager);
    physicsSimulator = std::dynamic_pointer_cast<IPhysicsSimulator<State>>(
        manager->getComponent(ComponentType::PhysicsSimulator));
}
