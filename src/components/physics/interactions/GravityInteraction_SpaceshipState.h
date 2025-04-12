//
// Created by arseniy on 12.4.25.
//

#ifndef GRAVITYINTERACTION_SPACESHIPSTATE_H
#define GRAVITYINTERACTION_SPACESHIPSTATE_H
#include "GravityInteraction.h"
#include "dto/envSettings/EnvSettingsAstro.h"

class GravityInteraction_SpaceshipState : public GravityInteraction<SpaceshipState>
{
public:
    explicit GravityInteraction_SpaceshipState(std::vector<CelestialBody> celestialBodies,
        std::shared_ptr<SpaceshipModel> spaceshipModel) :
        GravityInteraction<SpaceshipState>(celestialBodies, spaceshipModel) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
};

inline std::unique_ptr<IComponent> GravityInteraction_SpaceshipState::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    std::shared_ptr<EnvSettingsAstro> envSettingsAstro = std::dynamic_pointer_cast<EnvSettingsAstro>(context.envSettings);
    if (!envSettingsAstro)
    {
        spdlog::error("GravityInteraction_SpaceshipState - EnvSettings is not of type EnvSettingsAstro");
        throw std::runtime_error("GravityInteraction_SpaceshipState - EnvSettings is not of type EnvSettingsAstro");
    }
    return std::make_unique<GravityInteraction_SpaceshipState>(envSettingsAstro->celestialBodies, envSettingsAstro->spaceshipModel);
}

#endif //GRAVITYINTERACTION_SPACESHIPSTATE_H
