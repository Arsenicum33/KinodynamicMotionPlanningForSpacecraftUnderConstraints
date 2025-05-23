// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "AstrodynamicInterpolator.h"
#include "utils/PositionUtils.h"

std::unique_ptr<IComponent> AstrodynamicInterpolator::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double interpolationTimestep = std::any_cast<double>(configMap.at("timestep"));

    return std::make_unique<AstrodynamicInterpolator>(interpolationTimestep);
}

int AstrodynamicInterpolator::calculateInterpolationSteps(const SpaceshipState &from, const SpaceshipState &to)
{
    double timeDifference = to.time - from.time;

    int numSteps = timeDifference/interpolationTimestep;

    return numSteps;
}

SpaceshipState AstrodynamicInterpolator::interpolateBetweenPositions(const SpaceshipState &start,
    const SpaceshipState &end, double factor)
{
    return PositionUtils::interpolateSpaceshipStates(start, end, factor);
}
