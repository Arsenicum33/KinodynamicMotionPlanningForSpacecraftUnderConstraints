//
// Created by arseniy on 12.4.25.
//

#include "AstrodynamicBurstSampler.h"

#define MAIN_THRUSTER_FUEL_THRESHOLD 0.1
#define ROTATION_THRUSTER_FUEL_THRESHOLD 0.1

std::unique_ptr<IComponent> AstrodynamicBurstSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double thrustBurstMaxDuration = std::any_cast<double>(configMap.at("thrustBurstMaxDuration"));
    double torqueBurstMaxDuration = std::any_cast<double>(configMap.at("torqueBurstMaxDuration"));
    double zeroControlInputSamplingChance = std::any_cast<double>(configMap.at("zeroControlInputSamplingChance"));

    auto stabilizingSampler = StabilizingControlInputSampler::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<StabilizingControlInputSampler*>(stabilizingSampler.get()))
    {
        stabilizingSampler.release();
        std::unique_ptr<StabilizingControlInputSampler> baseSampler(castPtr);
        return std::make_unique<AstrodynamicBurstSampler>(std::move(baseSampler), thrustBurstMaxDuration, torqueBurstMaxDuration, zeroControlInputSamplingChance);
    }
    spdlog::error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
    throw std::runtime_error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
}

BurstControlInput AstrodynamicBurstSampler::sample(const SpaceshipState &currentPosition)
{
    if (std::generate_canonical<double, 10>(this->gen) < zeroControlInputSamplingChance)
    {
        return BurstControlInput(0.0, {0.0,0.0,0.0}, 0.0,0.0);
    }
    BurstControlInput controlInput = BurstControlInputSampler<SpaceshipState>::sample(currentPosition);
    double thrust = controlInput.getThrust(),
        thrustDuration=controlInput.getThrustBurstDuration(), torqueDuration = controlInput.getTorqueBurstDuration();
    std::array<double, 3> torque = controlInput.getTorque();
    if (currentPosition.getFuel().getMainThrusterFuel() < MAIN_THRUSTER_FUEL_THRESHOLD)
    {
        thrust = 0.0;
        thrustDuration = 0.0;
    }
    if (currentPosition.getFuel().getRotationThrustersFuel() < ROTATION_THRUSTER_FUEL_THRESHOLD)
    {
        torque = { 0.0,0.0,0.0};
        torqueDuration = 0.0;
    }
    return BurstControlInput(thrust, torque, thrustDuration, torqueDuration);
}
