//
// Created by arseniy on 17.1.25.
//

#include "DefaultDynamicExporter.h"

#include <fstream>
#include <poses/static/PoseMath.h>

#include "core/validator/IValidator.h"
#include "core/validator/Validator.h"
#include "poses/dynamic/KeyframeMath.h"

std::vector<Keyframe> DefaultDynamicExporter::exportPoses(std::vector<Keyframe> &keyframes)
{
    Json::Value root(Json::arrayValue);

    int frameCounter = 1;
    std::array<double, 3> eulersAngles;
    std::vector<Keyframe> discreteKeyframes = KeyframeMath::getKeyframesAtDiscreteTimes(keyframes);
    for (const auto& keyframe : discreteKeyframes)
    {
        Json::Value jsonPose;
        jsonPose["frame"] = frameCounter;

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

        // Add this pose to the root array
        root.append(jsonPose);
        frameCounter++;
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
    return discreteKeyframes;
}
