//
// Created by arseniy on 11.4.25.
//

#include "AstrodynamicExporter.h"

#include <utils/AnimationUtils.h>

#include "utils/ScalingUtils.h"
#include <utils/PhysicsUtils.h>

std::unique_ptr<IComponent> AstrodynamicExporter::createComponent(const ComponentConfig &config,
                                                                  const ReaderContext &context)
{
    const auto& configMap = config.config;

    std::string filename = std::any_cast<std::string>(configMap.at("filename"));
    double fps = std::any_cast<double>(configMap.at("fps"));
    return std::make_unique<AstrodynamicExporter>(filename,fps);
}

void AstrodynamicExporter::exportPositionsTyped(std::vector<SpaceshipState> positions) const
{
    scalePositions(positions);
    positions = AnimationUtils::getInterpolatedSpaceshipStatesAtRate(positions, fps);
    ATypedExporter<SpaceshipState>::exportPositionsTyped(positions);
}

Json::Value AstrodynamicExporter::exportPositionTyped(const SpaceshipState &state, int frame) const
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
    const Eigen::Quaterniond& quaternion = state.rotation;
    //quaternion.normalize();
    jsonRotation.append(quaternion.w());
    jsonRotation.append(quaternion.x());
    jsonRotation.append(quaternion.y());
    jsonRotation.append(quaternion.z());

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
        jsonAngularVelocity.append(angularVelocityCoord);
    }
    jsonPose["angularVelocity"] = jsonAngularVelocity;

    jsonPose["main_thruster_fuel"] = state.getFuel().getMainThrusterFuel();
    jsonPose["rotation_thruster_fuel"] = state.getFuel().getRotationThrustersFuel();

    return jsonPose;
}

void AstrodynamicExporter::scalePositions(std::vector<SpaceshipState> &positions) const
{
    for (auto& position : positions)
    {
        position.translation = PhysicsUtils::operator*(position.translation, 1/AU_TO_KM_SCALING_CONSTANT);
    }
}
