// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef ICOMPONENTMANAGER_H
#define ICOMPONENTMANAGER_H
#include "components/ComponentType.h"
#include "core/reader/IReader.h"

class IComponent;

class IComponentManager
{
public:
    virtual ~IComponentManager() = default;
    virtual void initialize(const ReaderContext& context) = 0;
    virtual std::shared_ptr<IComponent> getComponent(ComponentType componentType) = 0;
    virtual std::unique_ptr<IComponent> getUniqueComponent(ComponentType componentType, std::string tag = "") = 0;
    virtual const std::vector<std::shared_ptr<const IComponent>> getComponents() const = 0;
};

#endif //ICOMPONENTMANAGER_H
