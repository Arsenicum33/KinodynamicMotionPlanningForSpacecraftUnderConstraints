//
// Created by arseniy on 10.3.25.
//

#include "TemporalTransRotMetricFactory.h"

std::unique_ptr<TemporalTransRotMetric> TemporalTransRotMetricFactory::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));
    double temporalScalingFactor = std::any_cast<double>(configMap.at("temporalScalingFactor"));

    return std::make_unique<TemporalTransRotMetric>(temporalScalingFactor, rotationScalingFactor);
}
