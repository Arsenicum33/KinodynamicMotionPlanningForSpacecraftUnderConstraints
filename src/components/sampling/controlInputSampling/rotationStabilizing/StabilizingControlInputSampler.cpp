// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "StabilizingControlInputSampler.h"

std::unique_ptr<IComponent> StabilizingControlInputSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double thrust = std::any_cast<double>(configMap.at("thrust"));
    double stabilizingFactor = std::any_cast<double>(configMap.at("stabilizingFactor"));
    double maxAngularVelocity = std::any_cast<double>(context.sharedVariables.at("maxAngularVelocity"));
    double sigma = std::any_cast<double>(configMap.at("sigma"));

    std::vector<std::any> torqueAsVector = std::any_cast<std::vector<std::any>>(configMap.at("torque"));
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

    /*if (torque[1] != 0.0)
    {
        spdlog::error("Roll max acceleration must be 0");
        throw std::runtime_error("Roll max acceleration must be 0");
    }*/

    return std::make_unique<StabilizingControlInputSampler>(thrust, torque,
        stabilizingFactor, maxAngularVelocity, sigma);
}

ControlInput StabilizingControlInputSampler::sample(const State &currentPosition)
{
    double linearAcceleration = thrustDist(gen);
    std::array<double,3> angularAccelerations {0.0, 0.0, 0.0};
    for (int i = 0; i < 3; i+=2)
    {
        double angularVelocity = currentPosition.angularVelocity[i];
        double mu = - stabilizingFactor * (angularVelocity / maxAngularVelocity);
        std::normal_distribution<double> distribution(mu, sigma);
        double distributionValue = distribution(gen);
        double distributionValueClamed = std::clamp(distributionValue, -1.0, 1.0);
        angularAccelerations[i] = torque[i] * distributionValueClamed;
    }
    return ControlInput(linearAcceleration, angularAccelerations);
}
