//
// Created by arseniy on 3.1.25.
//

#ifndef ICOMPONENT_H
#define ICOMPONENT_H
#include "Capability.h"
#include "ComponentRegistry.h"
#include "core/creator/ComponentManager.h"

class IComponent
{
public:
    virtual ~IComponent() = default;
    virtual CapabilitySet getCapabilities() const = 0;
    virtual void resolveDependencies(ComponentConfig &config, ComponentManager *manager) {};
    virtual void build() {};
};



#endif //ICOMPONENT_H
