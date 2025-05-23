// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
#define PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
#include "PhysicsSimulator.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class AstrodynamicPhysicsSimulator : public PhysicsSimulator<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv}; }
};

inline std::unique_ptr<IComponent> AstrodynamicPhysicsSimulator::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<AstrodynamicPhysicsSimulator>();
}



#endif //PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
