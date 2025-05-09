//
// Created by arseniy on 12.4.25.
//

#ifndef INTERNALFORCESCOMPUTER_SPACESHIPSTATE_BURSTCI_H
#define INTERNALFORCESCOMPUTER_SPACESHIPSTATE_BURSTCI_H
#include "InternalForcesComputer.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class AstrodynamicInternalForcesComputer : public InternalForcesComputer<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv};};
};

inline std::unique_ptr<IComponent> AstrodynamicInternalForcesComputer::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<AstrodynamicInternalForcesComputer>();
}
#endif //INTERNALFORCESCOMPUTER_SPACESHIPSTATE_BURSTCI_H
