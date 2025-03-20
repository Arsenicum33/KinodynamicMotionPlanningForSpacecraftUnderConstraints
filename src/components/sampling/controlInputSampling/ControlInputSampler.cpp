//
// Created by arseniy on 20.3.25.
//

#include "ControlInputSampler.h"

std::unique_ptr<IComponent> ControlInputSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxLinearAccelerationModule = std::any_cast<double>(configMap.at("maxLinearAccelerationModule"));
    std::array<double, 3> maxAngularAccelerationModules = std::any_cast<std::array<double, 3>>(configMap.at("maxAngularAccelerationModules"));

    return std::make_unique<ControlInputSampler>(maxLinearAccelerationModule, maxAngularAccelerationModules);
}

ControlInput ControlInputSampler::sample()
{
    double linearAcceleration = linearAccelerationDist(gen);
    std::array<double,3> angularAccelerations ={
        angularAccelerationRollDist(gen),
        angularAccelerationPitchDist(gen),
        angularAccelerationYawDist(gen)
    };
    ControlInput controlInput(linearAcceleration, angularAccelerations);
    return controlInput;
}
