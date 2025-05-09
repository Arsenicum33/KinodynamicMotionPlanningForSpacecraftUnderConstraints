//
// Created by arseniy on 1.4.25.
//

#ifndef ENVSETTINGSASTRO_H
#define ENVSETTINGSASTRO_H
#include "EnvSettings.h"
#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"

class EnvSettingsAstro : public EnvSettings
{
public:
    EnvSettingsAstro(EnvSettings otherSettings,
        std::vector<CelestialBody> celestial_bodies)
        : EnvSettings(std::move(otherSettings)),
          celestialBodies(celestial_bodies)
    {}

    std::vector<CelestialBody> celestialBodies;
};

#endif //ENVSETTINGSASTRO_H
