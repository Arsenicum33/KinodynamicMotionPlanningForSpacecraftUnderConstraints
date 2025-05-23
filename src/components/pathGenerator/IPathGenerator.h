// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IPATHGENERATOR_H
#define IPATHGENERATOR_H
#include <memory>
#include <vector>

#include "components/IComponent.h"

class IPathGenerator  : public IComponent
{
public:
    ComponentType getType() const override { return ComponentType::PathGenerator; };

private:
};

#endif //IPATHGENERATOR_H
