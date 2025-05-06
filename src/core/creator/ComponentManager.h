//
// Created by arseniy on 13.1.25.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include "IComponentManager.h"


class ComponentManager : public IComponentManager
{
public:

    void initialize(const ReaderContext &context) override;

    std::shared_ptr<IComponent> getComponent(ComponentType componentType) override;
    std::unique_ptr<IComponent> getUniqueComponent(ComponentType componentType, std::string tag = "") override;

    const std::vector<std::shared_ptr<const IComponent>> getComponents() const override;

private:
    std::unique_ptr<ReaderContext> savedContext;
    std::unordered_map<ComponentType, std::shared_ptr<IComponent>> components;
    std::unordered_map<std::string, ComponentConfig> taggedComponents;
};



#endif //COMPONENTMANAGER_H
