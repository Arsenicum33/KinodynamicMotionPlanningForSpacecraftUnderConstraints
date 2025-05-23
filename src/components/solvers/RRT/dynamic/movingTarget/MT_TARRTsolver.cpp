// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "MT_TARRTsolver.h"

std::unique_ptr<IComponent> MT_TARRTsolver::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    int maxIterations = static_cast<int>(std::any_cast<double>(configMap.at("maxIterations")));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double velocity = std::any_cast<double>(configMap.at("velocity"));
    int outputPeriod = 10000;

    return std::make_unique<MT_TARRTsolver>(maxIterations, maxStepSize, velocity, outputPeriod);
}

Keyframe MT_TARRTsolver::getExtendedPosition(std::shared_ptr<const TreeNode<Keyframe>> neighbor, const Keyframe &sample)
{
    Keyframe intermediatePosition = interpolator->getIntermediatePosition(neighbor->pose, sample, maxStepSize);
    intermediatePosition.time = neighbor->pose.time + distanceMetric->getSpatialDistance(neighbor->pose, intermediatePosition)/velocity;
    return intermediatePosition;
}
