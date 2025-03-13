//
// Created by arseniy on 3.1.25.
//

#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "ComponentType.h"
#include "capabilities/Capability.h"
#include "core/creator/ComponentManager.h"

class IComponent
{
public:
    virtual ~IComponent() = default;
    virtual CapabilitySet getCapabilities() const = 0;

    virtual void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) {};
    virtual void build() {};
    virtual ComponentType getType() const = 0;
    std::string getName() const { return componentTypeToString(getType()); }
};



#endif //ICOMPONENT_H
