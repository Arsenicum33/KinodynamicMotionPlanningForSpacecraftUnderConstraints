//
// Created by arseniy on 2.1.25.
//

#include "Keyframe.h"

Keyframe Keyframe::operator+(const Keyframe &other) const
{
    Pose poseSum = Pose::operator+(other);
    return Keyframe(poseSum, this->time + other.time);
}

Keyframe Keyframe::operator*(double factor) const
{
    Pose poseMultiplied = Pose::operator*(factor);
    return Keyframe(poseMultiplied, this->time * factor);
}

std::string Keyframe::toString() const
{
    return Pose::toString() + "Time: " + std::to_string(time);
}

std::vector<double> Keyframe::flatten() const
{
    std::vector<double> flattenedPose = Pose::flatten();
    flattenedPose.push_back(time);
    return flattenedPose;
}

std::vector<double> Keyframe::flattenNoRot() const
{
    std::vector<double> result = Pose::flattenNoRot();
    result.push_back(time);
    return result;
}
