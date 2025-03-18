//
// Created by arseniy on 14.3.25.
//

#ifndef IINTERPOLATOR_H
#define IINTERPOLATOR_H
#include "components/IComponent.h"

template <typename PositionType>
class IInterpolator : public IComponent
{
public:
    virtual std::vector<PositionType> interpolate(const PositionType &start, const PositionType &end) = 0;
    virtual PositionType getIntermediatePosition(const PositionType &from, const PositionType &to, double stepSize) = 0;

    ComponentType getType() const override { return ComponentType::Interpolator; };
};

#endif //IINTERPOLATOR_H
