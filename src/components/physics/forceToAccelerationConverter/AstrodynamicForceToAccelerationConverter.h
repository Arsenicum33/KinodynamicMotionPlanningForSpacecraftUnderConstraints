// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef FORCETOACCELERATIONCONVERTER_SPACESHIPSTATE_H
#define FORCETOACCELERATIONCONVERTER_SPACESHIPSTATE_H
#include "ForceToAccelerationConverter.h"
#include "dto/envSettings/EnvSettingsAstro.h"

class AstrodynamicForceToAccelerationConverter : public ForceToAccelerationConverter<SpaceshipState>
{
public:

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv};}
};

inline std::unique_ptr<IComponent> AstrodynamicForceToAccelerationConverter::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<AstrodynamicForceToAccelerationConverter>();
}

#endif //FORCETOACCELERATIONCONVERTER_SPACESHIPSTATE_H
