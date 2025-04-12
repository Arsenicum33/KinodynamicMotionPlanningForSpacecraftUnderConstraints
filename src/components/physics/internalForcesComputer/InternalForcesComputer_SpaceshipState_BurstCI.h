//
// Created by arseniy on 12.4.25.
//

#ifndef INTERNALFORCESCOMPUTER_SPACESHIPSTATE_BURSTCI_H
#define INTERNALFORCESCOMPUTER_SPACESHIPSTATE_BURSTCI_H
#include "InternalForcesComputer.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class InternalForcesComputer_SpaceshipState_BurstCI : public InternalForcesComputer<SpaceshipState, BurstControlInput>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv};};
};

inline std::unique_ptr<IComponent> InternalForcesComputer_SpaceshipState_BurstCI::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<InternalForcesComputer_SpaceshipState_BurstCI>();
}
#endif //INTERNALFORCESCOMPUTER_SPACESHIPSTATE_BURSTCI_H
