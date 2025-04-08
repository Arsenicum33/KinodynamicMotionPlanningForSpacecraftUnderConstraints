//
// Created by arseniy on 22.3.25.
//

#include "DefaultKinodynamicExporter.h"

#include <dto/poses/static/poseMath/PoseMath.h>
#include <utils/PhysicsUtils.h>

#include "utils/AnimationUtils.h"
#include "utils/ScalingUtils.h"

#define ANGULAR_VELOCITY_SCALING_FACTOR 1e4

std::unique_ptr<IComponent> DefaultKinodynamicExporter::createComponent(const ComponentConfig &config,
                                                                        const ReaderContext &context)
{
    const auto& configMap = config.config;

    std::string filename = std::any_cast<std::string>(configMap.at("filename"));
    double fps = std::any_cast<double>(configMap.at("fps"));
    return std::make_unique<DefaultKinodynamicExporter>(filename,fps);
}

void DefaultKinodynamicExporter::exportPositionsTyped(std::vector<State> positions) const
{
    scalePositions(positions);
    positions = AnimationUtils::getInterpolatedStatesAtRate(positions, fps);
    ATypedExporter<State>::exportPositionsTyped(positions);
}

Json::Value DefaultKinodynamicExporter::exportPositionTyped(const State &state, int frame) const
{
    Json::Value jsonPose;
    jsonPose["time"] = state.time;

    Json::Value jsonPosition(Json::arrayValue);
    for (double coord : state.translation)
    {
        jsonPosition.append(coord);
    }
    jsonPose["position"] = jsonPosition;

    Json::Value jsonRotation(Json::arrayValue);
    std::array<double, 3> eulersAngles = PoseMath::rotationMatrixToEuler(state.rotation);
    for (double angle : eulersAngles)
    {
        jsonRotation.append(angle);
    }
    jsonPose["rotation"] = jsonRotation;

    Json::Value jsonVelocity(Json::arrayValue);
    for (double velocityCoord : state.velocity)
    {
        jsonVelocity.append(velocityCoord);
    }
    jsonPose["velocity"] = jsonVelocity;

    Json::Value jsonAngularVelocity(Json::arrayValue);
    for (double angularVelocityCoord : state.angularVelocity)
    {
        jsonAngularVelocity.append(angularVelocityCoord * ANGULAR_VELOCITY_SCALING_FACTOR);
    }
    jsonPose["angularVelocity"] = jsonAngularVelocity;

    return jsonPose;
}

void DefaultKinodynamicExporter::scalePositions(std::vector<State> &positions) const
{
    for (auto& position : positions)
    {
        position.translation = PhysicsUtils::operator*(position.translation, 1/AU_TO_KM_SCALING_CONSTANT);
    }
}
