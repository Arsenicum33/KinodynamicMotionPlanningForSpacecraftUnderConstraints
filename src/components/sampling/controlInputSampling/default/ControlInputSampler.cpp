// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "ControlInputSampler.h"

std::unique_ptr<IComponent> ControlInputSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double thrust = std::any_cast<double>(configMap.at("thrust"));
    std::vector<std::any> torqueAsVector = std::any_cast<std::vector<std::any>>(configMap.at("maxAngularAccelerationModules"));
    if (torqueAsVector.size() != 3)
    {
        spdlog::error("Max angular acceleration modules wrong array size. Must be 3");
        throw std::runtime_error("Max angular acceleration modules wrong array size");
    }
    std::array<double, 3> torque = {
        std::any_cast<Json::Value>(torqueAsVector[0]).asDouble(),
        std::any_cast<Json::Value>(torqueAsVector[1]).asDouble(),
        std::any_cast<Json::Value>(torqueAsVector[2]).asDouble()
    };

    return std::make_unique<ControlInputSampler>(thrust, torque);
}

ControlInput ControlInputSampler::sample(const State& currentPosition)
{
    double linearAcceleration = thrustDist(gen);
    std::array<double,3> angularAccelerations ={
        torquePitchDist(gen),
        torqueRollDist(gen),
        torqueYawDist(gen)
    };
    ControlInput controlInput(linearAcceleration, angularAccelerations);
    return controlInput;
}
