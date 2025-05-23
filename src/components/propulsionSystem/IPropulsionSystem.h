// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef IPROPULSIONSYSTEM_H
#define IPROPULSIONSYSTEM_H
#include <components/IComponent.h>

#include <dto/controlInputPlan/ControlInputPlan.h>

template <typename ControlInput>
class IPropulsionSystem : public IComponent
{
public:
    virtual ControlInputPlan generateControlInputPlan(const ControlInput& controlInput) = 0;
};
#endif //IPROPULSIONSYSTEM_H
