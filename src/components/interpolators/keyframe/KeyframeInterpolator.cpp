//
// Created by arseniy on 14.3.25.
//

#include "KeyframeInterpolator.h"

#include <poses/static/PoseMath.h>

std::vector<Keyframe> KeyframeInterpolator::interpolate(const Keyframe &start, const Keyframe &end)
{
    std::vector<Pose> interpolatedPoses = poseInterpolator.interpolate(start, end);
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

Keyframe KeyframeInterpolator::getIntermediatePosition(const Keyframe &from, const Keyframe &to, double stepSize)
{
    double distance = distanceMetric->getSpatialDistance(from, to);
    if (distance <= stepSize)
        return to;
    Pose intermediatePose = poseInterpolator.getIntermediatePosition(from, to, stepSize);
    double timeDiff = to.time - from.time;
    double intermediateTime = from.time + timeDiff * (stepSize / distance);
    return Keyframe(intermediatePose, intermediateTime);
}


std::vector<Keyframe> KeyframeInterpolator::getInterpolatedKeyframesAtRate(const std::vector<Keyframe> &keyframes,
                                                                           int fps)
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

Keyframe KeyframeInterpolator::getInterpolatedKeyframeAtTime(const Keyframe &before, const Keyframe &after, double time)
{
    if (before.time > time || after.time < time)
    {
        spdlog::error("KeyframeInterpolator::getInterpolatedKeyframeAtTime - time is out of range");
        throw std::invalid_argument("Time mist be between first and second keyframes times");
    }


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

void KeyframeInterpolator::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IKeyframeInterpolator::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}

Keyframe KeyframeInterpolator::extractKeyframeAtTime(DynamicObject<RAPID_model> *dynamicObject, double time)
{
    std::vector<Keyframe> keyframes = dynamicObject->getAnimation()->getKeyframes();
    if (dynamicObject->getAnimation()->isCyclic())
    {
        spdlog::error("KeyframeInterpolator::extractKeyframeAtTime - Keyframe cycle not implemented");
        throw std::runtime_error("KeyframeInterpolator::extractKeyframeAtTime: Keyframe cycle not implemented");
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
