// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IPOSITIONSAMPLER_H
#define IPOSITIONSAMPLER_H

#include "../../IComponent.h"

template <typename SampledType, typename TargetType>
class IPositionSampler : public IComponent
{
public:
    virtual SampledType sample(const TargetType& target) = 0;

    ComponentType getType() const override { return ComponentType::PositionSampler; };
};

#endif //IPOSITIONSAMPLER_H
