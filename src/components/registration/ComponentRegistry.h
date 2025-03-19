//
// Created by arseniy on 11.1.25.
//

#ifndef COMPONENTREGISTRY_H
#define COMPONENTREGISTRY_H

#include <any>
#include <functional>
#include <string>
#include <memory>
#include <components/IComponent.h>

#include "core/reader/IReader.h"

#define REGISTER_COMPONENT(ComponentType)                                   \
    bool ComponentType##_entry = ComponentRegistry<IComponent>::add(        \
        #ComponentType,                                                     \
        ComponentType::createComponent)                                     \


template <typename T>
class ComponentRegistry
{
public:
    using FactoryFunction = std::function<std::unique_ptr<T>(const ComponentConfig& config, const ReaderContext& context)>;
    using FactoryMap = std::unordered_map<std::string, FactoryFunction>;

    static bool add(const std::string& name, FactoryFunction fac)
    {
        auto& map = getFactoryMap();
        if (map.find(name) != map.end())
        {
            return false;
        }

        map[name] = fac;
        return true;
    }

    static std::unique_ptr<T> create(const ComponentConfig& config, const ReaderContext& context)
    {
        std::string name = config.type;
        auto& map = getFactoryMap();
        auto it = map.find(name);
        if (it == map.end())
        {
            throw std::runtime_error("Component not found: " + name);
        }
        return it->second(config, context);
    }

private:
    // Use Meyer's singleton to prevent SIOF
    static FactoryMap& getFactoryMap()
    {
        static FactoryMap map;
        return map;
    }
};



#endif //COMPONENTREGISTRY_H
