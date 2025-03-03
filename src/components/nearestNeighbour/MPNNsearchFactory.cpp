//
// Created by arseniy on 14.1.25.
//

#include "MPNNsearchFactory.h"

#include "MPNNsearch.h"

std::unique_ptr<AbstractNearestNeighbourSearch> MPNNsearchFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double dimensions = std::any_cast<double>(configMap.at("dimensions"));
    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_unique<MPNNsearch>(dimensions, maxNeightbours);
}
