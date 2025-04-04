//
// Created by arseniy on 14.3.25.
//

#include "StaticInterpolator.h"

#include <dto/poses/static/poseMath/PoseMath.h>

#include "utils/PositionUtils.h"


std::unique_ptr<IComponent> StaticInterpolator::createComponent(const ComponentConfig &config,
                                                                const ReaderContext &context)
{
    const auto& configMap = config.config;

    double interpolationThreshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<StaticInterpolator>(interpolationThreshold);
}

std::vector<Pose> StaticInterpolator::interpolate(const Pose &start, const Pose &end)
{
    double distance = distanceMetric->getSpatialDistance(start, end);

    int numSteps = distance / interpolationThreshold;

    if (numSteps <= 1)
    {
        return std::vector<Pose> { start, end};
    }

    std::vector<Pose> poses;

    for (int k = 0; k <= numSteps; k++)
    {
        double factor = static_cast<double>(k) / static_cast<double>(numSteps);
        Pose interpolatedPose = PositionUtils::interpolatePoses(start, end, factor);
        poses.push_back(interpolatedPose);
    }

    return poses;
}

Pose StaticInterpolator::getIntermediatePosition(const Pose &from, const Pose &to, double stepSize)
{
    double distance = distanceMetric->getSpatialDistance(from, to);
    if (distance <= stepSize)
    {
        return to;
    }

    double factor = stepSize / distance;

    return PositionUtils::interpolatePoses(from, to, factor);
}
