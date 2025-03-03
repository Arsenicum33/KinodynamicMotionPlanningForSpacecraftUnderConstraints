//
// Created by arseniy on 13.1.25.
//

#ifndef ICOMPONENTMANAGER_H
#define ICOMPONENTMANAGER_H
#include "core/reader/IReader.h"

class IComponent;

class IComponentManager
{
public:
    virtual ~IComponentManager() = default;
    virtual void initialize(const ReaderContext& context) = 0;
    virtual std::shared_ptr<IComponent> getComponent(const std::string& name) = 0;
    virtual std::unique_ptr<IComponent> getUniqueComponent(const std::string &name) = 0;
    virtual const std::vector<std::shared_ptr<const IComponent>> getComponents() const = 0;
};

#endif //ICOMPONENTMANAGER_H
