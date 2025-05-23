// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "KinodynamicPlanner.h"

std::unique_ptr<IComponent> KinodynamicPlanner::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double timeResolution = std::any_cast<double>(configMap.at("timeResolution"));

    return std::make_unique<KinodynamicPlanner>(timeResolution);
}
