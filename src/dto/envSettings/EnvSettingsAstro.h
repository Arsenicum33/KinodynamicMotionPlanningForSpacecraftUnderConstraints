//
// Created by arseniy on 1.4.25.
//

#ifndef ENVSETTINGSASTRO_H
#define ENVSETTINGSASTRO_H
#include "EnvSettings.h"
#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"
#include "dto/spaceshipModel/SpaceshipModel.h"

class EnvSettingsAstro : public EnvSettings
{
public:
    EnvSettingsAstro(EnvSettings otherSettings,
        std::vector<CelestialBody> celestial_bodies,
        std::shared_ptr<SpaceshipModel> spaceshipModel)
        : EnvSettings(std::move(otherSettings)),
          celestialBodies(celestial_bodies),
        spaceshipModel(spaceshipModel)
    {}

    std::vector<CelestialBody> celestialBodies;
    std::shared_ptr<SpaceshipModel> spaceshipModel;
};

#endif //ENVSETTINGSASTRO_H
