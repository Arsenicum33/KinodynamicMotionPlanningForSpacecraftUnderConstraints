//
// Created by arseniy on 9.5.25.
//

#include "KinodynamicSSTsolver.h"

std::unique_ptr<IComponent> KinodynamicSSTsolver::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    int maxIterations = static_cast<int>(std::any_cast<double>(configMap.at("maxIterations")));
    double selectionRadius = std::any_cast<double>(configMap.at("selectionRadius"));
    double maxWitnessProximityRadius = std::any_cast<double>(configMap.at("maxWitnessProximityRadius"));

    return std::make_unique<KinodynamicSSTsolver>(maxIterations,selectionRadius, maxWitnessProximityRadius);
}
