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
    //if (before.time > time || after.time < time)
   //     throw std::invalid_argument("Time mist be between first and second keyframes times");
    if (before.time > time)
        return before;
    if (after.time < time)
        return after;

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

std::vector<Keyframe> KeyframeMath::getInterpolatedKeyframesAtRate(const std::vector<Keyframe>& keyframes, int fps)
{
    std::vector<Keyframe> interpolatedKeyframes;
    for (int i=0; i<keyframes.size()-1; i++)
    {
        const Keyframe& firstKeyframe = keyframes[i];
        interpolatedKeyframes.push_back(firstKeyframe);
        const Keyframe& secondKeyframe = keyframes[i+1];
        double dt = secondKeyframe.time - firstKeyframe.time;
        int numberOfFrames = round(dt*fps);
        int numberOfInbetweenFrames = numberOfFrames-2;
        if (numberOfInbetweenFrames <= 0)
            continue;
        int numberOfTimeIntervals = numberOfInbetweenFrames + 1;
        double lengthOfInterval = dt / numberOfTimeIntervals;
        for (int j=1; j<=numberOfInbetweenFrames; j++)
        {
            double frameTime = firstKeyframe.time + j * lengthOfInterval;
            Keyframe keyframe = getInterpolatedKeyframeAtTime(firstKeyframe, secondKeyframe, frameTime);
            interpolatedKeyframes.push_back(keyframe);
        }
    }
    interpolatedKeyframes.push_back(keyframes.back());
    return interpolatedKeyframes;
}
