// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef SPACESHIPSTATEPROPAGATOR_H
#define SPACESHIPSTATEPROPAGATOR_H
#include "StatePropagator.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class AstrodynamicStatePropagator : public StatePropagator<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; }
};

inline std::unique_ptr<IComponent> AstrodynamicStatePropagator::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<AstrodynamicStatePropagator>();
}

#endif //SPACESHIPSTATEPROPAGATOR_H
