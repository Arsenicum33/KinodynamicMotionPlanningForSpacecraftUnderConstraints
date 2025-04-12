//
// Created by arseniy on 12.4.25.
//

#include "KinodynamicBurstSampler.h"

std::unique_ptr<IComponent> KinodynamicBurstSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double thrustBurstMaxDuration = std::any_cast<double>(configMap.at("thrustBurstMaxDuration"));
    double torqueBurstMaxDuration = std::any_cast<double>(configMap.at("torqueBurstMaxDuration"));

    auto stabilizingSampler = StabilizingControlInputSampler::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<StabilizingControlInputSampler*>(stabilizingSampler.get()))
    {
        stabilizingSampler.release();
        std::unique_ptr<StabilizingControlInputSampler> baseSampler(castPtr);
        return std::make_unique<KinodynamicBurstSampler>(std::move(baseSampler), thrustBurstMaxDuration, torqueBurstMaxDuration);
    }
    spdlog::error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
    throw std::runtime_error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
}
