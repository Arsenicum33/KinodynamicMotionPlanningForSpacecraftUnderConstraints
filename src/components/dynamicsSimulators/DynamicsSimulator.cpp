//
// Created by arseniy on 21.3.25.
//

#include "DynamicsSimulator.h"

#include <dto/poses/static/poseMath/PoseMath.h>
#define ZERO_ROTATION_THRESHOLD 1e-6

std::unique_ptr<IComponent> DynamicsSimulator::createComponent(const ComponentConfig &config,
                                                               const ReaderContext &context)
{
    return std::make_unique<DynamicsSimulator>();
}

State DynamicsSimulator::computeNextState(const State &currentState, const TotalAcceleration &totalAcceleration, double timestep)
{
    using namespace PhysicsUtils;

    const std::array<double, 3>& linearAcceleration = totalAcceleration.getLinearAcceleration();
    const std::array<double,3>& angularAcceleration = totalAcceleration.getAngularAcceleration();

    std::array<double,3> newTranslation = currentState.translation + currentState.velocity * timestep +
        0.5 * linearAcceleration * timestep * timestep;
    std::array<double,3> newVelocity = currentState.velocity + linearAcceleration * timestep;

    std::array<double,3> newAngularVelocity = currentState.angularVelocity + angularAcceleration * timestep;
    Eigen::Quaterniond currentRotation = PoseMath::rotationMatrixToQuaternion(currentState.rotation);

    std::array<double,3> averageAngularVelocity = (currentState.angularVelocity + newAngularVelocity) * 0.5;
    double averageAngularSpeed = std::sqrt(
        averageAngularVelocity[0] * averageAngularVelocity[0] +
        averageAngularVelocity[1] * averageAngularVelocity[1] +
        averageAngularVelocity[2] * averageAngularVelocity[2]
    );
    Eigen::Quaterniond rotationChange;
    if (averageAngularSpeed > ZERO_ROTATION_THRESHOLD)
    {
        Eigen::Vector3d axis(
        averageAngularVelocity[0] / averageAngularSpeed,
        averageAngularVelocity[1] / averageAngularSpeed,
        averageAngularVelocity[2] / averageAngularSpeed
        );
        double angle = averageAngularSpeed * timestep;
        rotationChange = Eigen::Quaterniond(Eigen::AngleAxisd(angle, axis));
    }
    else
    {
        rotationChange = Eigen::Quaterniond::Identity();
    }
    Eigen::Quaterniond newRotation = rotationChange * currentRotation;
    newRotation.normalize();
    double newTime = currentState.time + timestep;
    State result(newTranslation, newRotation, newTime, newVelocity, newAngularVelocity);
    return result;
}
