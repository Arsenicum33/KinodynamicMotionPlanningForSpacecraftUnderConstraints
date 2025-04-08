//
// Created by arseniy on 7.4.25.
//

#include "BurstControlInputSampler.h"

std::unique_ptr<IComponent> BurstControlInputSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double burstMaxDuration = std::any_cast<double>(configMap.at("burstMaxDuration"));

    auto stabilizingSampler = StabilizingControlInputSampler::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<StabilizingControlInputSampler*>(stabilizingSampler.get()))
    {
        stabilizingSampler.release();
        std::unique_ptr<StabilizingControlInputSampler> baseSampler(castPtr);
        return std::make_unique<BurstControlInputSampler>(std::move(baseSampler), burstMaxDuration);
    }
    spdlog::error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
    throw std::runtime_error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
}

BurstControlInput BurstControlInputSampler::sample(const State &currentPosition)
{
    ControlInput controlInput = stabilizingControlInputSampler->sample(currentPosition);
    double duration = burstDurationDist(gen);
    BurstControlInput burstControlInput(controlInput, duration);
    return burstControlInput;
}
