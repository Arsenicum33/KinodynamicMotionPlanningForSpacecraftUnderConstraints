// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
