// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "AstrodynamicSSTsolver.h"

std::unique_ptr<IComponent> AstrodynamicSSTsolver::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    int maxIterations = static_cast<int>(std::any_cast<double>(configMap.at("maxIterations")));
    double selectionRadius = std::any_cast<double>(configMap.at("selectionRadius"));
    double maxWitnessProximityRadius = std::any_cast<double>(configMap.at("maxWitnessProximityRadius"));

    return std::make_unique<AstrodynamicSSTsolver>(maxIterations,selectionRadius, maxWitnessProximityRadius);
}
