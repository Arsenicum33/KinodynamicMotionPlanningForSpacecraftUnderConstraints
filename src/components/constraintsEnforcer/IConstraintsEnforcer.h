// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ICONSTRAINTSENFORCER_H
#define ICONSTRAINTSENFORCER_H
#include <components/IComponent.h>

template <typename PositionType>
class IConstraintsEnforcer : public IComponent
{
public:
    virtual bool satisfiesConstraints(const PositionType& position) const = 0;

    ComponentType getType() const override { return ComponentType::ConstraintsEnforcer; };
};

#endif //ICONSTRAINTSENFORCER_H
