//
// Created by arseniy on 14.1.25.
//

#include "MPNNsearchFactory.h"

#include "MPNNsearch.h"

std::shared_ptr<AbstractNearestNeighbourSearch> MPNNsearchFactory::createComponent(ComponentConfig &config,
                                                                                   ReaderContext &context)
{
    const auto& configMap = config.config;

    double dimensions = std::any_cast<double>(configMap.at("dimensions"));
    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_shared<MPNNsearch>(dimensions, maxNeightbours);
}
