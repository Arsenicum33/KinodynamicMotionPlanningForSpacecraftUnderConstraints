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

    auto stabilizingSampler = StabilizingControlInputSampler::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<StabilizingControlInputSampler*>(stabilizingSampler.get()))
    {
        stabilizingSampler.release();
        std::unique_ptr<StabilizingControlInputSampler> baseSampler(castPtr);
        return std::make_unique<AstrodynamicBurstSampler>(std::move(baseSampler), thrustBurstMaxDuration, torqueBurstMaxDuration);
    }
    spdlog::error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
    throw std::runtime_error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
}

BurstControlInput AstrodynamicBurstSampler::sample(const SpaceshipState &currentPosition)
{
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
