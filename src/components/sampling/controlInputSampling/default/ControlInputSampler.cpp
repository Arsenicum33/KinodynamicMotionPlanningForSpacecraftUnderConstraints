//
// Created by arseniy on 20.3.25.
//

#include "ControlInputSampler.h"

std::unique_ptr<IComponent> ControlInputSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxLinearAccelerationModule = std::any_cast<double>(configMap.at("maxLinearAccelerationModule"));
    std::vector<std::any> maxAngularAccelerationModulesAsVector = std::any_cast<std::vector<std::any>>(configMap.at("maxAngularAccelerationModules"));
    if (maxAngularAccelerationModulesAsVector.size() != 3)
    {
        spdlog::error("Max angular acceleration modules wrong array size. Must be 3");
        throw std::runtime_error("Max angular acceleration modules wrong array size");
    }
    std::array<double, 3> maxAngularAccelerationModules = {
        std::any_cast<Json::Value>(maxAngularAccelerationModulesAsVector[0]).asDouble(),
        std::any_cast<Json::Value>(maxAngularAccelerationModulesAsVector[1]).asDouble(),
        std::any_cast<Json::Value>(maxAngularAccelerationModulesAsVector[2]).asDouble()
    };

    return std::make_unique<ControlInputSampler>(maxLinearAccelerationModule, maxAngularAccelerationModules);
}

ControlInput ControlInputSampler::sample(const State& currentPosition)
{
    double linearAcceleration = linearAccelerationDist(gen);
    std::array<double,3> angularAccelerations ={
        angularAccelerationPitchDist(gen),
        angularAccelerationRollDist(gen),
        angularAccelerationYawDist(gen)
    };
    ControlInput controlInput(linearAcceleration, angularAccelerations);
    return controlInput;
}
