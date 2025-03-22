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

    auto staticComponent = StaticInterpolator::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<IStaticInterpolator*>(staticComponent.get()))
    {
        staticComponent.release();
        std::unique_ptr<IStaticInterpolator> staticInterpolator(castPtr);
        return std::make_unique<DynamicInterpolator>(std::move(staticInterpolator), interpolationThreshold);
    }
    spdlog::error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
    throw std::runtime_error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
}

std::vector<Keyframe> DynamicInterpolator::interpolate(const Keyframe &start, const Keyframe &end)
{
    double distance = distanceMetric->getSpatialDistance(start, end);

    int numSteps = distance / interpolationThreshold;
    std::vector<Keyframe> keyframes;
    if (numSteps <= 1)
    {
        return std::vector<Keyframe> { start, end};
    }
    for (int k = 0; k <= numSteps; k++)
    {
        double factor = static_cast<double>(k) / static_cast<double>(numSteps);
        Keyframe interpolatedKeyframe = PositionUtils::interpolateKeyframes(start, end, factor);
        keyframes.push_back(interpolatedKeyframe);
    }

    return keyframes;
}

Keyframe DynamicInterpolator::getIntermediatePosition(const Keyframe &from, const Keyframe &to, double stepSize)
{
    double distance = distanceMetric->getSpatialDistance(from, to);
    if (distance <= stepSize)
        return to;
    double factor = stepSize / distance;
    return PositionUtils::interpolateKeyframes(from, to, factor);
}

void DynamicInterpolator::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IDynamicInterpolator::resolveDependencies(config, manager);
    staticInterpolator->resolveDependencies(config, manager);
}
