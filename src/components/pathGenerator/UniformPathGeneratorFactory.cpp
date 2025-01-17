//
// Created by arseniy on 14.1.25.
//

#include "UniformPathGeneratorFactory.h"

#include "UniformPathGenerator.h"

std::shared_ptr<IPathGenerator<Pose>> UniformPathGeneratorFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double interpolationThreshold = std::any_cast<double>(configMap.at("interpolationThreshold"));
    double interpolationRotationThreshold = std::any_cast<double>(configMap.at("interpolationRotationThreshold"));
    double desiredNumberOfFrames = std::any_cast<double>(configMap.at("desiredNumberOfFrames"));

    return std::make_shared<UniformPathGenerator>(interpolationThreshold, interpolationRotationThreshold, desiredNumberOfFrames);
}
