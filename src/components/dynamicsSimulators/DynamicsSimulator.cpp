//
// Created by arseniy on 21.3.25.
//

#include "DynamicsSimulator.h"

#include <dto/poses/static/poseMath/PoseMath.h>

std::unique_ptr<IComponent> DynamicsSimulator::createComponent(const ComponentConfig &config,
                                                               const ReaderContext &context)
{
    const auto& configMap = config.config;

    double timestep = std::any_cast<double>(configMap.at("timestep"));

    return std::make_unique<DynamicsSimulator>(timestep);
}

State DynamicsSimulator::computeNextState(const State &currentState, const ControlInput &controlInput)
{
    using namespace PhysicsUtils;
    double linearAcceleration = controlInput.getLinearAcceleration();
    const std::array<double,3>& angularAcceleration = controlInput.getAngularAcceleration();
    std::array<double,3> directionVectorGlobal { currentState.rotation[0][1], currentState.rotation[1][1], currentState.rotation[2][1]};
    std::array<double,3> accelerationVector = directionVectorGlobal * linearAcceleration;
    std::array<double,3> newTranslation = currentState.translation + currentState.velocity * timeStep +
        0.5 * accelerationVector * timeStep * timeStep;
    std::array<double,3> newVelocity = currentState.velocity + accelerationVector * timeStep;
    std::array<double,3> newAngularVelocity = currentState.angularVelocity + angularAcceleration * timeStep;
    Eigen::Quaterniond currentRotation = PoseMath::rotationMatrixToQuaternion(currentState.rotation);

    double angularSpeed = std::sqrt(
        currentState.angularVelocity[0] * currentState.angularVelocity[0] +
        currentState.angularVelocity[1] * currentState.angularVelocity[1] +
        currentState.angularVelocity[2] * currentState.angularVelocity[2]
    );
    Eigen::Quaterniond rotationChange;
    if (angularSpeed > 1e-6) {
        Eigen::Vector3d axis(
            currentState.angularVelocity[0] / angularSpeed,
            currentState.angularVelocity[1] / angularSpeed,
            currentState.angularVelocity[2] / angularSpeed
        );
        double angle = angularSpeed * timeStep;
        rotationChange = Eigen::Quaterniond(Eigen::AngleAxisd(angle, axis));
    } else {
        rotationChange = Eigen::Quaterniond::Identity();
    }
    Eigen::Quaterniond newRotation = rotationChange * currentRotation;
    newRotation.normalize();
    double newTime = currentState.time + timeStep;
    State result(newTranslation, newRotation, newTime, newVelocity, newAngularVelocity);
    return result;
}
