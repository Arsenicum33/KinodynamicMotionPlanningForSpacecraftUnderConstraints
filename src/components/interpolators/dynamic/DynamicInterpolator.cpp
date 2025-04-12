//
// Created by arseniy on 14.3.25.
//

#include "DynamicInterpolator.h"

#include <dto/poses/static/poseMath/PoseMath.h>

#include "utils/PositionUtils.h"


std::unique_ptr<IComponent> DynamicInterpolator::createComponent(const ComponentConfig &config,
                                                                 const ReaderContext &context)
{
    const auto& configMap = config.config;

    double interpolationThreshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<DynamicInterpolator>(interpolationThreshold);
}

int DynamicInterpolator::calculateInterpolationSteps(const Keyframe &from, const Keyframe &to)
{
    double distance = distanceMetric->getSpatialDistance(from, to);
    int numSteps = distance / interpolationThreshold;
    return numSteps;
}

Keyframe DynamicInterpolator::interpolateBetweenPositions(const Keyframe &start, const Keyframe &end, double factor)
{
    return PositionUtils::interpolateKeyframes(start, end, factor);
}
