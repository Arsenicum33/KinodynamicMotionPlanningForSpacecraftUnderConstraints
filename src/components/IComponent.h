//
// Created by arseniy on 3.1.25.
//

#ifndef ICOMPONENT_H
#define ICOMPONENT_H
#include "Capability.h"
#include "ComponentRegistry.h"

class IComponent
{
public:
    virtual ~IComponent() = default;
    virtual CapabilitySet getCapabilities() const = 0;
};



#endif //ICOMPONENT_H
