//
// Created by arseniy on 8.4.25.
//

#include "QuaternionRotationExporter.h"

#include <dto/poses/static/poseMath/PoseMath.h>

std::unique_ptr<IComponent> QuaternionRotationExporter::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    std::string filename = std::any_cast<std::string>(configMap.at("filename"));
    double fps = std::any_cast<double>(configMap.at("fps"));
    return std::make_unique<QuaternionRotationExporter>(filename,fps);
}

Json::Value QuaternionRotationExporter::exportPositionTyped(const State &state, int frame) const
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
    Eigen::Quaterniond quaternion = PoseMath::rotationMatrixToQuaternion(state.rotation);
    quaternion.normalize();
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

    return jsonPose;
}
