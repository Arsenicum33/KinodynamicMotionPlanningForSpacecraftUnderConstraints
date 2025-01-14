//
// Created by arseniy on 14.1.25.
//

#include "WeightedTransRotMetricFactory.h"

#include "WeightedTranslationRotationMetric.h"

std::shared_ptr<IDistanceMetric> WeightedTransRotMetricFactory::createComponent(ComponentConfig &config,
                                                                                ReaderContext &context)
{
    const auto& configMap = config.config;

    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));

    return std::make_shared<WeightedTranslationRotationMetric>(rotationScalingFactor);
}
