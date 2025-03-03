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

    std::shared_ptr<IComponent> getComponent(const std::string& name) override;
    std::unique_ptr<IComponent> getUniqueComponent(const std::string &name) override;

    const std::vector<std::shared_ptr<const IComponent>> getComponents() const override;

private:
    std::unique_ptr<ReaderContext> savedContext;
    std::unordered_map<std::string, std::shared_ptr<IComponent>> components;
};



#endif //COMPONENTMANAGER_H
