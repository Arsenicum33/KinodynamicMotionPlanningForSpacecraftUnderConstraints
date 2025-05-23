// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef MOVINGTARGETTERMINATIONCONDITION_H
#define MOVINGTARGETTERMINATIONCONDITION_H

#include "components/distanceMeasurement/temporalTotal/ITotalDistanceMetric.h"
#include "components/interpolators/IInterpolator.h"
#include "components/terminationConditions/ITerminationCondition.h"


class MovingTargetTerminationCondition : public ITerminationCondition<Keyframe, Animation>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    MovingTargetTerminationCondition(double threshold) : ITerminationCondition<Keyframe, Animation>(threshold) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv, Capability::MovingTarget, Capability::KinodynamicEnv}; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    double computeDistance(const Keyframe &currentPosition, const Animation &target) override;

private:
    std::shared_ptr<ITotalDistanceMetric<Keyframe>> distanceMetric;
};

#endif //MOVINGTARGETTERMINATIONCONDITION_H
