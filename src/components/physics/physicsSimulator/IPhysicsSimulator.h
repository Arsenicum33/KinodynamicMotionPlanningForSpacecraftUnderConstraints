// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IPHYSICSSIMULATOR_H
#define IPHYSICSSIMULATOR_H
#include <components/IComponent.h>
#include <dto/totalAcceleration/TotalAcceleration.h>

template <typename StateType>
class IPhysicsSimulator : public IComponent
{
public:
    virtual TotalAcceleration computeAcceleration(const StateType& currentState, const BurstControlInput& controlInput) = 0;

    ComponentType getType() const override { return ComponentType::PhysicsSimulator; };
};

#endif //IPHYSICSSIMULATOR_H
