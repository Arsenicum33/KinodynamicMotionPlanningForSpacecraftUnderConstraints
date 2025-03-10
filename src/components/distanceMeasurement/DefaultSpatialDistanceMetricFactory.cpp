//
// Created by arseniy on 14.1.25.
//

#include "DefaultSpatialDistanceMetricFactory.h"

#include "DefaultSpatialDistanceMetric.h"

std::unique_ptr<DefaultSpatialDistanceMetric> DefaultSpatialDistanceMetricFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));

    return std::make_unique<DefaultSpatialDistanceMetric>(rotationScalingFactor);
}
