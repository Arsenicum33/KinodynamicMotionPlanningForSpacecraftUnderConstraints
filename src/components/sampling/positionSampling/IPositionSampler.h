//
// Created by arseniy on 28.10.24.
//

#ifndef IPOSITIONSAMPLER_H
#define IPOSITIONSAMPLER_H

#include "../../IComponent.h"

template <typename SampledType, typename TargetType>
class IPositionSampler : public IComponent
{
public:
    virtual SampledType sample(TargetType target) = 0;

    ComponentType getType() const override { return ComponentType::PositionSampler; };
};

#endif //IPOSITIONSAMPLER_H
