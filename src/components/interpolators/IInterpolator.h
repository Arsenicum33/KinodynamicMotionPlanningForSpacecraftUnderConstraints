//
// Created by arseniy on 14.3.25.
//

#ifndef IINTERPOLATOR_H
#define IINTERPOLATOR_H
#include "components/IComponent.h"

template <typename T>
class IInterpolator : public IComponent
{
public:
    virtual std::vector<T> interpolate(const T &start, const T &end) = 0;
    virtual T getIntermediatePosition(const T &from, const T &to, double stepSize) = 0;

    ComponentType getType() const override { return ComponentType::Interpolator; };
};

#endif //IINTERPOLATOR_H
