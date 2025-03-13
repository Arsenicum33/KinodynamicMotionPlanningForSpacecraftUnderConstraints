//
// Created by arseniy on 14.1.25.
//

#include "MPNNsearchFactory.h"

#include "MPNNsearch.h"

std::unique_ptr<AbstractNearestNeighbourSearch<Pose>> MPNNsearchFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_unique<MPNNsearch>(maxNeightbours);
}
