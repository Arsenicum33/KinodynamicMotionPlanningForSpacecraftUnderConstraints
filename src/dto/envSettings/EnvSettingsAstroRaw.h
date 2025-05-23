// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ENVSETTINGSASTRORAW_H
#define ENVSETTINGSASTRORAW_H
#include <any>

#include "EnvSettingsRaw.h"

class EnvSettingsAstroRaw : public EnvSettingsRaw
{
public:
    EnvSettingsAstroRaw(const EnvSettingsRaw& otherSettings,
         std::unordered_map<std::string, std::unordered_map<std::string, std::any>> celestial_bodies)
        : EnvSettingsRaw(otherSettings) ,celestialBodies(celestial_bodies)
    {}

    std::unordered_map<std::string, std::unordered_map<std::string, std::any>> celestialBodies;
};

#endif //ENVSETTINGSASTRORAW_H
