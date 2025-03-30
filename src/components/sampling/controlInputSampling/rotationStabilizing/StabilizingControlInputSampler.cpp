//
// Created by arseniy on 26.3.25.
//

#include "StabilizingControlInputSampler.h"

std::unique_ptr<IComponent> StabilizingControlInputSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxLinearAccelerationModule = std::any_cast<double>(configMap.at("maxLinearAccelerationModule"));
    double stabilizingFactor = std::any_cast<double>(configMap.at("stabilizingFactor"));
    double maxAngularVelocity = std::any_cast<double>(context.sharedVariables.at("maxAngularVelocity"));
    double sigma = std::any_cast<double>(configMap.at("sigma"));

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

    if (maxAngularAccelerationModules[1] != 0.0)
    {
        spdlog::error("Roll max acceleration must be 0");
        throw std::runtime_error("Roll max acceleration must be 0");
    }

    return std::make_unique<StabilizingControlInputSampler>(maxLinearAccelerationModule, maxAngularAccelerationModules,
        stabilizingFactor, maxAngularVelocity, sigma);
}

ControlInput StabilizingControlInputSampler::sample(const State &currentPosition)
{
    double linearAcceleration = linearAccelerationDist(gen);
    std::array<double,3> angularAccelerations {0.0, 0.0, 0.0};
    for (int i = 0; i < 3; i+=2)
    {
        double angularVelocity = currentPosition.angularVelocity[i];
        double mu = - stabilizingFactor * (angularVelocity / maxAngularVelocity);
        std::normal_distribution<double> distribution(mu, sigma);
        double distributionValue = distribution(gen);
        double distributionValueClamed = std::clamp(distributionValue, -1.0, 1.0);
        angularAccelerations[i] = maxAngularAccelerationModules[i] * distributionValueClamed;
    }
    return ControlInput(linearAcceleration, angularAccelerations);
}
