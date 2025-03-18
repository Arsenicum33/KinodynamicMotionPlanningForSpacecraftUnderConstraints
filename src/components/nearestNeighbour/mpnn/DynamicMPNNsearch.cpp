//
// Created by arseniy on 18.3.25.
//

#include "DynamicMPNNsearch.h"

std::unique_ptr<IComponent> DynamicMPNNsearch::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_unique<DynamicMPNNsearch>(maxNeightbours);
}
