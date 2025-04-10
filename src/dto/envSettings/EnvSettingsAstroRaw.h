//
// Created by arseniy on 1.4.25.
//

#ifndef ENVSETTINGSASTRORAW_H
#define ENVSETTINGSASTRORAW_H
#include <any>

#include "EnvSettingsRaw.h"

class EnvSettingsAstroRaw : public EnvSettingsRaw
{
public:
    EnvSettingsAstroRaw(const EnvSettingsRaw& otherSettings,
         std::unordered_map<std::string, std::unordered_map<std::string, std::any>> celestial_bodies,
         std::unordered_map<std::string, std::any> spaceshipModel)
        : EnvSettingsRaw(otherSettings) ,celestialBodies(celestial_bodies), spaceshipModel(spaceshipModel)
    {}

    std::unordered_map<std::string, std::unordered_map<std::string, std::any>> celestialBodies;
    std::unordered_map<std::string, std::any> spaceshipModel;
};

#endif //ENVSETTINGSASTRORAW_H
