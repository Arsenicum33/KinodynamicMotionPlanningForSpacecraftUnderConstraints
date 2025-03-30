//
// Created by arseniy on 17.3.25.
//

#include "TARRTsolver.h"

std::unique_ptr<IComponent> TAGeometricRRTsolver::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    int maxIterations = static_cast<int>(std::any_cast<double>(configMap.at("maxIterations")));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double velocity = std::any_cast<double>(configMap.at("velocity"));
    int outputPeriod = 10000;

    return std::make_unique<TAGeometricRRTsolver>(maxIterations, maxStepSize, velocity, outputPeriod);
}

Keyframe TAGeometricRRTsolver::getExtendedPosition(std::shared_ptr<const TreeNode<Keyframe>> neighbor, const Keyframe &sample)
{
    Keyframe intermediatePosition = interpolator->getIntermediatePosition(neighbor->pose, sample, maxStepSize);
    intermediatePosition.time = neighbor->pose.time + distanceMetric->getSpatialDistance(neighbor->pose, intermediatePosition)/velocity;
    return intermediatePosition;
}
