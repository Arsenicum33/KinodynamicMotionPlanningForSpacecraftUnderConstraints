// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IDERIVATOR_H
#define IDERIVATOR_H
#include <components/IComponent.h>

#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

template <typename StateType>
class IDerivator : public IComponent
{
public:
    virtual StateType derive(const StateType& currentState, const BurstControlInput& controlInput) = 0 ;

    ComponentType getType() const override { return ComponentType::Derivator; };
};

#endif //IDERIVATOR_H
