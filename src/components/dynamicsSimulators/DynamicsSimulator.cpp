//
// Created by arseniy on 21.3.25.
//

#include "DynamicsSimulator.h"

#include <dto/poses/static/poseMath/PoseMath.h>
#define ZERO_ROTATION_THRESHOLD 1e-6

std::unique_ptr<IComponent> DynamicsSimulator::createComponent(const ComponentConfig &config,
                                                               const ReaderContext &context)
{
    const auto& configMap = config.config;

    return std::make_unique<DynamicsSimulator>();
}

State DynamicsSimulator::computeSegmentTransition(const State &currentState,
    const ForcesProfile<ControlInput>::Segment& segment)
{
    using namespace PhysicsUtils;
    const ControlInput& controlInput = *(segment.controlInput.get());
    double duration = segment.duration;

    double linearAcceleration = controlInput.getLinearAcceleration();
    const std::array<double,3>& angularAcceleration = controlInput.getAngularAcceleration();
    std::array<double,3> directionVectorGlobal { currentState.rotation[0][1], currentState.rotation[1][1], currentState.rotation[2][1]};
    std::array<double,3> accelerationVector = directionVectorGlobal * linearAcceleration;
    std::array<double,3> newTranslation = currentState.translation + currentState.velocity * duration +
        0.5 * accelerationVector * duration * duration;
    std::array<double,3> newVelocity = currentState.velocity + accelerationVector * duration;
    std::array<double,3> newAngularVelocity = currentState.angularVelocity + angularAcceleration * duration;
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
        double angle = averageAngularSpeed * duration;
        rotationChange = Eigen::Quaterniond(Eigen::AngleAxisd(angle, axis));
    }
    else
    {
        rotationChange = Eigen::Quaterniond::Identity();
    }
    Eigen::Quaterniond newRotation = rotationChange * currentRotation;
    newRotation.normalize();
    double newTime = currentState.time + duration;
    State result(newTranslation, newRotation, newTime, newVelocity, newAngularVelocity);
    return result;
}