//
// Created by arseniy on 13.1.25.
//

#include "ComponentManager.h"

#include <spdlog/spdlog.h>

#include "components/registration/ComponentRegistry.h"


void ComponentManager::initialize(const ReaderContext &context)
{
    savedContext = std::make_unique<ReaderContext>(context);

    for (const auto& componentConfig : context.componentConfigs)
    {
        if (components.find(componentConfig.name) != components.end())
        {
            spdlog::error("Duplicate component name: {}", componentConfig.name);
            throw std::runtime_error("Component already registered");
        }
         components[componentConfig.name] = std::move(ComponentRegistry<IComponent>::create(componentConfig, context));
    }

    for (const ComponentConfig &componentConfig : context.componentConfigs)
    {
        auto component = getComponent(componentConfig.name);
        if (!component)
        {
            spdlog::error("Component not found: {}", componentConfig.name);
            throw std::runtime_error("Component not found");
        }

        component->resolveDependencies(componentConfig, this);
    }

    for (auto& entry: components)
    {
        entry.second->build();
    }

    spdlog::info("Components registration successful");


}

std::shared_ptr<IComponent> ComponentManager::getComponent(const std::string &name)
{
    auto it = components.find(name);
    if (it == components.end())
        return nullptr;
    return it->second;
}

std::unique_ptr<IComponent> ComponentManager::getUniqueComponent(const std::string &name)
{
    for (auto& componentConfig : savedContext->componentConfigs)
    {
        if (componentConfig.name == name)
        {
            auto component = ComponentRegistry<IComponent>::create(componentConfig, *(savedContext.get()));
            component->resolveDependencies(componentConfig, this);
            component->build();
            return component;
        }
    }
    return nullptr;
}

const std::vector<std::shared_ptr<const IComponent>> ComponentManager::getComponents() const
{
    std::vector<std::shared_ptr<const IComponent>> components;
    components.reserve(this->components.size());
    for (const auto& [key, value] : this->components)
    {
        components.push_back(value);
    }
    return components;
}
