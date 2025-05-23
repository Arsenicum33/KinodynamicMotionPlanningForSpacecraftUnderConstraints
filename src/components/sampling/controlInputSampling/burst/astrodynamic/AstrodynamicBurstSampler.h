// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ASTRODYNAMICBURSTSAMPLER_H
#define ASTRODYNAMICBURSTSAMPLER_H
#include "components/sampling/controlInputSampling/burst/BurstControlInputSampler.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"
#include "random"
#include "components/fuelSystem/FuelSystem.h"

class AstrodynamicBurstSampler : public BurstControlInputSampler<SpaceshipState>
{
public:
    AstrodynamicBurstSampler(std::unique_ptr<StabilizingControlInputSampler> stabilizingControlInputSampler,
        double thrustBurstMaxDuration, double torqueBurstMaxDuration, double zeroControlInputSamplingChance)
        : BurstControlInputSampler<SpaceshipState>(
            std::move(stabilizingControlInputSampler), thrustBurstMaxDuration, torqueBurstMaxDuration),
    zeroControlInputSamplingChance(zeroControlInputSamplingChance) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; }

    BurstControlInput sample(const SpaceshipState &currentPosition) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    std::shared_ptr<FuelSystem> fuelSystem;
    double zeroControlInputSamplingChance;
};



#endif //ASTRODYNAMICBURSTSAMPLER_H
