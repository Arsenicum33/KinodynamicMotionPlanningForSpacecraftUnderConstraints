//
// Created by arseniy on 22.3.25.
//

#include "DefaultKinodynamicExporter.h"

#include <dto/poses/static/poseMath/PoseMath.h>

#include "utils/AnimationUtils.h"

void DefaultKinodynamicExporter::exportPositionsTyped(std::vector<State> positions) const
{
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
        jsonAngularVelocity.append(angularVelocityCoord);
    }
    jsonPose["angularVelocity"] = jsonAngularVelocity;

    return jsonPose;
}
