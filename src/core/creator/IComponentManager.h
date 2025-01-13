//
// Created by arseniy on 13.1.25.
//

#ifndef ICOMPONENTMANAGER_H
#define ICOMPONENTMANAGER_H
#include "components/IComponent.h"
#include "core/reader/IReader.h"

class IComponentManager
{
public:
    virtual ~IComponentManager() = default;
    virtual void initialize(const ReaderContext& context) = 0;
    virtual IComponent* getComponent() = 0;
};

#endif //ICOMPONENTMANAGER_H
