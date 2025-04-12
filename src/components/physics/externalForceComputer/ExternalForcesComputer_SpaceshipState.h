//
// Created by arseniy on 12.4.25.
//

#ifndef EXTERNALFORCESCOMPUTER_SPACESHIPSTATE_H
#define EXTERNALFORCESCOMPUTER_SPACESHIPSTATE_H
#include "ExternalForcesComputer.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"

class ExternalForcesComputer_SpaceshipState : public ExternalForcesComputer<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv};};
};

inline std::unique_ptr<IComponent> ExternalForcesComputer_SpaceshipState::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<ExternalForcesComputer_SpaceshipState>();
}

#endif //EXTERNALFORCESCOMPUTER_SPACESHIPSTATE_H
