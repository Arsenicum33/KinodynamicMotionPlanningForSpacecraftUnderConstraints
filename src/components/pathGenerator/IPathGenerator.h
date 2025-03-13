//
// Created by arseniy on 8.11.24.
//

#ifndef IPATHGENERATOR_H
#define IPATHGENERATOR_H
#include <memory>
#include <vector>

#include "components/IComponent.h"

class IPathGenerator  : public IComponent
{
public:
    ComponentType getType() const override { return ComponentType::PathGenerator; };

private:;
};

#endif //IPATHGENERATOR_H
