//
// Created by arseniy on 17.1.25.
//

#include "DefaultDynamicExporter.h"

#include <fstream>
#include <poses/static/PoseMath.h>

#include "core/validator/IValidator.h"
#include "core/validator/Validator.h"
#include "poses/dynamic/KeyframeMath.h"

std::unique_ptr<IComponent> DefaultDynamicExporter::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    std::string filename = std::any_cast<std::string>(configMap.at("filename"));
    int fps = static_cast<int>(std::any_cast<double>(configMap.at("fps")));
    return std::make_unique<DefaultDynamicExporter>(filename,fps);
}


void DefaultDynamicExporter::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ATypedExporter<Keyframe>::resolveDependencies(config, manager);
    interpolator = std::dynamic_pointer_cast<IDynamicInterpolator>(manager->getComponent(ComponentType::Interpolator));
}

void DefaultDynamicExporter::exportPositionsTyped(std::vector<Keyframe> positions) const
{
    Json::Value root(Json::arrayValue);
    std::vector<Keyframe> interpolatedKeyframes = interpolator->getInterpolatedKeyframesAtRate(positions, fps);
    std::array<double, 3> eulersAngles;
    for (const auto& keyframe : interpolatedKeyframes)
    {
        Json::Value jsonPose;
        jsonPose["time"] = keyframe.time;

        // Add position (x, y, z)
        Json::Value jsonPosition(Json::arrayValue);
        for (double coord : keyframe.translation)
        {
            jsonPosition.append(coord);
        }
        jsonPose["position"] = jsonPosition;

        // Add rotation (rx, ry, rz)
        Json::Value jsonRotation(Json::arrayValue);
        eulersAngles = PoseMath::rotationMatrixToEuler(keyframe.rotation);
        for (double angle : eulersAngles)
        {
            jsonRotation.append(angle);
        }
        jsonPose["rotation"] = jsonRotation;

        // Add this static to the root array
        root.append(jsonPose);
    }

    // Write the JSON array to the output file
    std::ofstream file(filename, std::ofstream::out);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    // Write the JSON content to the file
    Json::StreamWriterBuilder writer;
    std::unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
    jsonWriter->write(root, &file);
    file.close();
}
