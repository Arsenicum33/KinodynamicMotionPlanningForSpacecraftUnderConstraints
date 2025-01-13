//
// Created by arseniy on 13.1.25.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include "IComponentManager.h"


class ComponentManager : public IComponentManager
{
public:
    ComponentManager();
    void initialize(const ReaderContext &context) override;

    IComponent * getComponent() override;
};



#endif //COMPONENTMANAGER_H
