// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IINTERNALFORCESCOMPUTER_H
#define IINTERNALFORCESCOMPUTER_H
#include <components/IComponent.h>

#include "components/physics/totalForce/TotalForce.h"

template <typename StateType>
class IInternalForcesComputer : public IComponent
{
public:
    virtual TotalForce computeTotalForce(const StateType& state, const BurstControlInput& controlInput) = 0;

    ComponentType getType() const override { return ComponentType::InternalForcesComputer; }
};

#endif //IINTERNALFORCESCOMPUTER_H
