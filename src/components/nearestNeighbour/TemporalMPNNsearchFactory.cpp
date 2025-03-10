//
// Created by arseniy on 10.3.25.
//

#include "TemporalMPNNsearchFactory.h"

std::unique_ptr<TemporalMPNNsearch> TemporalMPNNsearchFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_unique<TemporalMPNNsearch>(maxNeightbours);
}
