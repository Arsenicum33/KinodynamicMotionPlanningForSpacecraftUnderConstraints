//
// Created by arseniy on 14.3.25.
//

#ifndef KEYFRAMEINTERPOLATOR_H
#define KEYFRAMEINTERPOLATOR_H
#include <components/distanceMeasurement/IDistanceMetric.h>

#include "components/collisionHandlers/static/IStaticCollisionHandler.h"
#include "components/interpolators/static/StaticInterpolator.h"


class DynamicInterpolator : public AInterpolator<Keyframe>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    DynamicInterpolator(double interpolationThreshold) :
        interpolationThreshold(interpolationThreshold) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::DynamicEnv, Capability::MovingTarget}; };

protected:
    int calculateInterpolationSteps(const Keyframe &from, const Keyframe &to) override;

    Keyframe interpolateBetweenPositions(const Keyframe &start, const Keyframe &end, double factor) override;

    double interpolationThreshold;

};



#endif //KEYFRAMEINTERPOLATOR_H
