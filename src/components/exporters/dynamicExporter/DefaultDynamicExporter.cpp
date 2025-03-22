//
// Created by arseniy on 17.1.25.
//

#include "DefaultDynamicExporter.h"

#include <fstream>
#include <dto/poses/static/poseMath/PoseMath.h>

#include "core/validator/IValidator.h"
#include "core/validator/Validator.h"
#include "utils/AnimationUtils.h"

std::unique_ptr<IComponent> DefaultDynamicExporter::createComponent(const ComponentConfig &config,
                                                                    const ReaderContext &context)
{
    const auto& configMap = config.config;

    std::string filename = std::any_cast<std::string>(configMap.at("filename"));
    int fps = static_cast<int>(std::any_cast<double>(configMap.at("fps")));
    return std::make_unique<DefaultDynamicExporter>(filename,fps);
}

Json::Value DefaultDynamicExporter::exportPositionTyped(const Keyframe &keyframe, int frame) const
{
    Json::Value jsonPose;
    jsonPose["time"] = keyframe.time;

    Json::Value jsonPosition(Json::arrayValue);
    for (double coord : keyframe.translation)
    {
        jsonPosition.append(coord);
    }
    jsonPose["position"] = jsonPosition;

    Json::Value jsonRotation(Json::arrayValue);
    std::array<double, 3> eulersAngles = PoseMath::rotationMatrixToEuler(keyframe.rotation);
    for (double angle : eulersAngles)
    {
        jsonRotation.append(angle);
    }
    jsonPose["rotation"] = jsonRotation;

    return jsonPose;
}

void DefaultDynamicExporter::exportPositionsTyped(std::vector<Keyframe> positions) const
{
    positions = AnimationUtils::getInterpolatedKeyframesAtRate(positions, fps);
    ATypedExporter<Keyframe>::exportPositionsTyped(positions);
}
