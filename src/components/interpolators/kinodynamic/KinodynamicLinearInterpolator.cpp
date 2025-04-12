//
// Created by arseniy on 22.3.25.
//

#include "KinodynamicLinearInterpolator.h"

#include <dto/poses/static/poseMath/PoseMath.h>

#include "utils/PositionUtils.h"

std::unique_ptr<IComponent> KinodynamicLinearInterpolator::createComponent(const ComponentConfig &config,
                                                                           const ReaderContext &context)
{
    const auto& configMap = config.config;

    double interpolationTimestep = std::any_cast<double>(configMap.at("timestep"));

    return std::make_unique<KinodynamicLinearInterpolator>(interpolationTimestep);
}

int KinodynamicLinearInterpolator::calculateInterpolationSteps(const State &from, const State &to)
{
    double timeDifference = to.time - from.time;

    int numSteps = timeDifference/interpolationTimestep;

    return numSteps;
}

State KinodynamicLinearInterpolator::interpolateBetweenPositions(const State &start, const State &end, double factor)
{
    return PositionUtils::interpolateStates(start, end, factor);
}

