//
// Created by arseniy on 8.3.25.
//

#ifndef MOVINGTARGETTERMINATIONCONDITION_H
#define MOVINGTARGETTERMINATIONCONDITION_H
#include <components/distanceMeasurement/IDistanceMetric.h>

#include "ITerminationCondition.h"


class MovingTargetTerminationCondition : public ITerminationCondition<Keyframe, Animation>
{
public:
    MovingTargetTerminationCondition(double threshold) : threshold(threshold) {}
    CapabilitySet getCapabilities() const override { return CapabilitySet {Capability::MovingTarget}; }

    bool isTargetReached(const Keyframe &currentPosition, const Animation &target) const override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    std::shared_ptr<IDistanceMetric> distanceMetric;
    double threshold;
};



#endif //MOVINGTARGETTERMINATIONCONDITION_H
