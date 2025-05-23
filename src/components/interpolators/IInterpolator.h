// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IINTERPOLATOR_H
#define IINTERPOLATOR_H
#include "components/IComponent.h"
#include "components/distanceMeasurement/IDistanceMetric.h"
template <typename PositionType>
class IInterpolator : public IComponent
{
public:
    virtual std::vector<PositionType> interpolate(const PositionType &start, const PositionType &end) = 0;
    virtual PositionType getIntermediatePosition(const PositionType &from, const PositionType &to, double stepSize) = 0;

    ComponentType getType() const override { return ComponentType::Interpolator; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override
    {
        distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
    };

protected:
    std::shared_ptr<IDistanceMetric> distanceMetric;
};

#endif //IINTERPOLATOR_H
