//
// Created by arseniy on 13.1.25.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include "IComponentManager.h"


class ComponentManager : public IComponentManager
{
public:
    void initialize(ReaderContext &context) override;

    std::shared_ptr<IComponent> getComponent(const std::string& name) override;
private:
    std::unordered_map<std::string, std::shared_ptr<IComponent>> components;
};



#endif //COMPONENTMANAGER_H
