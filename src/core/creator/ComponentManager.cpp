// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "ComponentManager.h"

#include <spdlog/spdlog.h>

#include "components/registration/ComponentRegistry.h"


void ComponentManager::initialize(const ReaderContext &context)
{
    savedContext = std::make_unique<ReaderContext>(context);

    for (const auto& componentConfig : context.componentConfigs)
    {
        if (componentConfig.tag != "")
        {
            if (taggedComponents.contains(componentConfig.tag))
            {
                spdlog::error("Duplicate tag: {}", componentConfig.tag);
                throw std::runtime_error("Duplicate tag");
            }
            taggedComponents[componentConfig.tag] = componentConfig;
            continue;
        }

        ComponentType type = stringToComponentType(componentConfig.name);
        if (components.find(type) != components.end() )
        {
            spdlog::error("Duplicate component name: {}", componentConfig.name);
            throw std::runtime_error("Component already registered");
        }
         components[type] = std::move(ComponentRegistry<IComponent>::create(componentConfig, context));
    }

    for (const ComponentConfig &componentConfig : context.componentConfigs)
    {
        if (componentConfig.tag != "")
            continue;
        ComponentType type = stringToComponentType(componentConfig.name);
        auto component = getComponent(type);
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

std::shared_ptr<IComponent> ComponentManager::getComponent(ComponentType componentType)
{
    auto it = components.find(componentType);
    if (it == components.end())
        return nullptr;
    return it->second;
}

std::unique_ptr<IComponent> ComponentManager::getUniqueComponent(ComponentType componentType, std::string tag)
{
    if (tag!="")
    {
        ComponentConfig config = taggedComponents.at(tag);
        if (componentType != stringToComponentType(config.name))
        {
            spdlog::error("Component not found: {}", tag);
            throw std::runtime_error("Component not found");
        }
        auto component = ComponentRegistry<IComponent>::create(config, *(savedContext.get()));
        component->resolveDependencies(config, this);
        component->build();
        return component;
    }
    for (auto& componentConfig : savedContext->componentConfigs)
    {
        ComponentType type = stringToComponentType(componentConfig.name);
        if (type== componentType)
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
