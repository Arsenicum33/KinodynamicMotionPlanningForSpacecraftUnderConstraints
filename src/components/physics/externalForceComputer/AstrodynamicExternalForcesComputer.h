// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef EXTERNALFORCESCOMPUTER_SPACESHIPSTATE_H
#define EXTERNALFORCESCOMPUTER_SPACESHIPSTATE_H
#include "ExternalForcesComputer.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"

class AstrodynamicExternalForcesComputer : public ExternalForcesComputer<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv};};
};

inline std::unique_ptr<IComponent> AstrodynamicExternalForcesComputer::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<AstrodynamicExternalForcesComputer>();
}

#endif //EXTERNALFORCESCOMPUTER_SPACESHIPSTATE_H
