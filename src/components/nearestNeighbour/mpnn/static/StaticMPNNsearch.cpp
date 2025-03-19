//
// Created by arseniy on 18.3.25.
//

#include "StaticMPNNsearch.h"

std::unique_ptr<IComponent> StaticMPNNsearch::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_unique<StaticMPNNsearch>(maxNeightbours);
}
