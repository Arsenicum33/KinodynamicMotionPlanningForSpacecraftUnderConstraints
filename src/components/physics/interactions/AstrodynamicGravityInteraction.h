//
// Created by arseniy on 12.4.25.
//

#ifndef GRAVITYINTERACTION_SPACESHIPSTATE_H
#define GRAVITYINTERACTION_SPACESHIPSTATE_H
#include "GravityInteraction.h"
#include "dto/envSettings/EnvSettingsAstro.h"

class AstrodynamicGravityInteraction : public GravityInteraction<SpaceshipState>
{
public:
    explicit AstrodynamicGravityInteraction(std::vector<CelestialBody> celestialBodies) :
        GravityInteraction<SpaceshipState>(celestialBodies) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
};

inline std::unique_ptr<IComponent> AstrodynamicGravityInteraction::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    std::shared_ptr<EnvSettingsAstro> envSettingsAstro = std::dynamic_pointer_cast<EnvSettingsAstro>(context.envSettings);
    if (!envSettingsAstro)
    {
        spdlog::error("AstrodynamicGravityInteraction - EnvSettings is not of type EnvSettingsAstro");
        throw std::runtime_error("AstrodynamicGravityInteraction - EnvSettings is not of type EnvSettingsAstro");
    }
    return std::make_unique<AstrodynamicGravityInteraction>(envSettingsAstro->celestialBodies);
}

#endif //GRAVITYINTERACTION_SPACESHIPSTATE_H
