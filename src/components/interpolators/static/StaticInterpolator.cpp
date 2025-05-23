// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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

int StaticInterpolator::calculateInterpolationSteps(const Pose &from, const Pose &to)
{
    double distance = distanceMetric->getSpatialDistance(from, to);

    int numSteps = distance / interpolationThreshold;

    return numSteps;
}

Pose StaticInterpolator::interpolateBetweenPositions(const Pose &start, const Pose &end, double factor)
{
    return PositionUtils::interpolatePoses(start, end, factor);
}
