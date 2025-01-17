//
// Created by arseniy on 15.1.25.
//

#include "KeyframeMath.h"

#include <poses/static/PoseMath.h>

Keyframe KeyframeMath::getKeyframeAtTime(DynamicObject<RAPID_model>* dynamicObject, double time)
{
    std::vector<Keyframe> keyframes = dynamicObject->getAnimation()->getKeyframes();
    if (dynamicObject->getAnimation()->isCyclic())
    {
        throw std::runtime_error("KeyframeMath::getKeyframeAtTime: Keyframe cycle not implemented");
    }
    for (int i=1;i<keyframes.size(); i++)
    {
        if (keyframes[i].time >= time)
        {
            Keyframe& beforeTime = keyframes[i-1];
            Keyframe& afterTime = keyframes[i];
            return getInterpolatedKeyframeAtTime(beforeTime, afterTime, time);
        }
    }
    Keyframe lastKeyframe = keyframes[keyframes.size()-1];
    return Keyframe(lastKeyframe.translation, lastKeyframe.rotation, time);
}

Keyframe KeyframeMath::getInterpolatedKeyframeAtTime(const Keyframe &before,const Keyframe &after, double time)
{
    if (before.time > time || after.time < time)
        throw std::invalid_argument("Time mist be between first and second keyframes times");

    double factor = (time - before.time) / (after.time - before.time);

    std::array<double, 3> newTranslation = {
        before.translation[0] + factor * (after.translation[0] - before.translation[0]),
        before.translation[1] + factor * (after.translation[1] - before.translation[1]),
        before.translation[2] + factor * (after.translation[2] - before.translation[2])
    };

    Eigen::Quaterniond rotationStart = PoseMath::rotationMatrixToQuaternion(before.rotation);
    Eigen::Quaterniond rotationEnd = PoseMath::rotationMatrixToQuaternion(after.rotation);
    Eigen::Quaterniond newRotation = rotationStart.slerp(factor, rotationEnd);

    Keyframe result(newTranslation, newRotation, time);
    return result;
}

std::vector<Keyframe> KeyframeMath::interpolateKeyframes(const Keyframe &start, const Keyframe &end,
    double interpolationThreshold, double rotationThreshold)
{
    std::vector<Pose> interpolatedPoses = PoseMath::interpolatePoses(start, end, interpolationThreshold, rotationThreshold);
    std::vector<Keyframe> keyframes;
    double startTime = start.time;
    double endTime = end.time;
    double timeDiff = endTime - startTime;
    double timeDiffBetweenFrames = timeDiff / (interpolatedPoses.size()-1);
    double currentTime = startTime;
    for (auto& pose : interpolatedPoses)
    {
        keyframes.push_back(PoseMath::poseToKeyframe(pose,currentTime));
        currentTime += timeDiffBetweenFrames;
    }
    return keyframes;
}

std::vector<Keyframe> KeyframeMath::getKeyframesAtDiscreteTimes(const std::vector<Keyframe>& keyframes)
{
    std::vector<Keyframe> keyframesDiscrete;
    if (keyframes[0].time != 1)
        throw std::runtime_error("keyframe times must start with 1");
    int frameIndex = 1;
    keyframesDiscrete.push_back(Keyframe(keyframes[0].translation, keyframes[0].rotation, frameIndex++));
    for (int i=1;i<keyframes.size();i++)
    {
        if (keyframes[i].time > frameIndex)
        {
            Keyframe nextFrame = getInterpolatedKeyframeAtTime(keyframes[i-1], keyframes[i], frameIndex++);
            keyframesDiscrete.push_back(nextFrame);
        }
    }
    return keyframesDiscrete;
}
