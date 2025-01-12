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

#define REGISTER_COMPONENT(ComponentType, FactoryType)                                   \
    bool ComponentType##_entry = ComponentRegistry<IComponent>::add(                    \
        #ComponentType,                                                                 \
        std::function<IComponent*(std::unordered_map<std::string, std::any>)>(          \
            [](std::unordered_map<std::string, std::any> data) -> IComponent* {         \
                static FactoryType factoryInstance;                                     \
                return factoryInstance.createComponent(std::move(data));                \
            }))


template <typename T>
class ComponentRegistry
{
public:
    using FactoryFunction = std::function<T*(std::unordered_map<std::string, std::any>)>;
    using FactoryMap = std::unordered_map<std::string, std::function<T*(std::unordered_map<std::string, std::any>)>>;

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

    static T* create(const std::string& name, std::unordered_map<std::string, std::any> data)
    {
        auto& map = getFactoryMap();
        auto it = map.find(name);
        if (it == map.end())
        {
            throw std::runtime_error("Component not found: " + name);
        }
        return it->second(std::move(data));
    }

//private:
    // Use Meyer's singleton to prevent SIOF
    static FactoryMap& getFactoryMap()
    {
        static FactoryMap map;
        return map;
    }
};



#endif //COMPONENTREGISTRY_H
