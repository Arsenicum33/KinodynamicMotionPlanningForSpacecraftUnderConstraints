//
// Created by arseniy on 25.10.24.
//

#ifndef ENVSETTINGS_H
#define ENVSETTINGS_H
#include <variant>
#include <poses/dynamic/DynamicObject.h>

#include "ConfigurationSpaceBoundaries.h"
#include "input/ComponentsParser.h"
#include "poses/static/Pose.h"

class EnvSettings
{
public:
    EnvSettings(Pose start_pose, std::variant<Pose, std::shared_ptr<DynamicObject<RAPID_model>>> target,
        std::shared_ptr<RAPID_model> agent, std::vector<std::shared_ptr<RAPID_model>> obstacles,
        std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamic_objects,
        ConfigurationSpaceBoundaries boundaries)
        : startPose(start_pose),
          target(std::move(target)),
          agent(agent),
          obstacles(obstacles),
          dynamicObjects(dynamic_objects),
          boundaries(boundaries)
    {
    }

    Pose startPose;
    std::variant<Pose, std::shared_ptr<DynamicObject<RAPID_model>>> target;
    std::shared_ptr<RAPID_model> agent;
    std::vector<std::shared_ptr<RAPID_model>> obstacles;
    std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    std::vector<ComponentConfig> componentConfigs;
    std::unordered_map<std::string, std::any> sharedVariables;
    ConfigurationSpaceBoundaries boundaries;
};

#endif //ENVSETTINGS_H
