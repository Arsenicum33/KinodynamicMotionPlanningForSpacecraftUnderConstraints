//
// Created by arseniy on 12.4.25.
//

#ifndef FORCETOACCELERATIONCONVERTER_SPACESHIPSTATE_H
#define FORCETOACCELERATIONCONVERTER_SPACESHIPSTATE_H
#include "ForceToAccelerationConverter.h"
#include "dto/envSettings/EnvSettingsAstro.h"

class ForceToAccelerationConverter_SpaceshipState : public ForceToAccelerationConverter<SpaceshipState>
{
public:
    explicit ForceToAccelerationConverter_SpaceshipState(std::shared_ptr<SpaceshipModel> spaceshipModel)
        : ForceToAccelerationConverter<SpaceshipState>(spaceshipModel) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
};

inline std::unique_ptr<IComponent> ForceToAccelerationConverter_SpaceshipState::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    std::shared_ptr<EnvSettingsAstro> envSettingsAstro = std::dynamic_pointer_cast<EnvSettingsAstro>(context.envSettings);
    if (!envSettingsAstro)
    {
        spdlog::error("ForceToAccelerationConverter_SpaceshipState - EnvSettings is not of type EnvSettingsAstro");
        throw std::runtime_error("ForceToAccelerationConverter_SpaceshipState - EnvSettings is not of type EnvSettingsAstro");
    }
    return std::make_unique<ForceToAccelerationConverter_SpaceshipState>(envSettingsAstro->spaceshipModel);
}

#endif //FORCETOACCELERATIONCONVERTER_SPACESHIPSTATE_H
