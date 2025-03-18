//
// Created by arseniy on 28.10.24.
//

#ifndef ISAMPLER_H
#define ISAMPLER_H

#include "poses/static/Pose.h"
#include "components/IComponent.h"

template <typename PositionType, typename TargetType>
class ISampler : public IComponent
{
public:
    virtual PositionType sample(TargetType target) = 0;

    ComponentType getType() const override { return ComponentType::Sampler; };
};

#endif //ISAMPLER_H
