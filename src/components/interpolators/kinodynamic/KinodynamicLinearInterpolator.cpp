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
    double maxInterpolationTimeDifference = std::any_cast<double>(configMap.at("maxTimeDifference"));

    return std::make_unique<KinodynamicLinearInterpolator>(interpolationTimestep, maxInterpolationTimeDifference);
}

std::vector<State> KinodynamicLinearInterpolator::interpolate(const State &start, const State &end)
{
    double timeDifference = end.time - start.time;
    if (timeDifference > maxInterpolationTimeDifference)
    {
        spdlog::error("KinodynamicLinearInterpolator::interpolate() - time difference is too big. Linearity asssumption does not hold");
        throw std::invalid_argument("KinodynamicLinearInterpolator::interpolate() - time difference is too big");
    }
    int numSteps = timeDifference/interpolationTimestep;
    if (numSteps <= 1)
    {
        return std::vector<State> { start, end};
    }
    std::vector<State> states;
    for (int k = 0; k <= numSteps; k++)
    {
        double factor = static_cast<double>(k) / static_cast<double>(numSteps);
        State interpolatedState = PositionUtils::interpolateStates(start, end, factor);
        states.push_back(interpolatedState);
    }
    return states;
}

State KinodynamicLinearInterpolator::getIntermediatePosition(const State &from, const State &to, double stepSize)
{
    double distance = distanceMetric->getSpatialDistance(from, to);
    if (distance <= stepSize)
        return to;
    double factor = stepSize / distance;
    return PositionUtils::interpolateStates(from, to, factor);
}

