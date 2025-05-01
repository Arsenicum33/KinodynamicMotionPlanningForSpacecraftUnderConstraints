//
// Created by arseniy on 12.4.25.
//

#ifndef SPACESHIPSTATEPROPAGATOR_H
#define SPACESHIPSTATEPROPAGATOR_H
#include "StatePropagator.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class SpaceshipStatePropagator : public StatePropagator<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; }
};

inline std::unique_ptr<IComponent> SpaceshipStatePropagator::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<SpaceshipStatePropagator>();
}

#endif //SPACESHIPSTATEPROPAGATOR_H
