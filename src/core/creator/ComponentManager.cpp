//
// Created by arseniy on 13.1.25.
//

#include "ComponentManager.h"

#include "components/ComponentRegistry.h"

void ComponentManager::initialize(ReaderContext &context)
{

    for (auto& componentConfig : context.componentConfigs)
    {
        if (components.find(componentConfig.name) != components.end()) {
            throw std::runtime_error("Duplicate component name: '" + componentConfig.name + "'");
        }
         components[componentConfig.name] = ComponentRegistry<IComponent>::create(componentConfig, context);
    }

    for (ComponentConfig &componentConfig : context.componentConfigs)
    {
        auto component = getComponent(componentConfig.name);
        if (!component)
            throw std::runtime_error("Could not find component '" + componentConfig.name);
        component->resolveDependencies(componentConfig, this);
    }

    for (auto& entry: components)
    {
        entry.second->build();
    }


}

std::shared_ptr<IComponent> ComponentManager::getComponent(const std::string &name)
{
    auto it = components.find(name);
    return it != components.end() ? it->second : nullptr;
}
