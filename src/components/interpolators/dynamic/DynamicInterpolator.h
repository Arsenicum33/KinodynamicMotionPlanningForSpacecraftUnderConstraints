//
// Created by arseniy on 14.3.25.
//

#ifndef KEYFRAMEINTERPOLATOR_H
#define KEYFRAMEINTERPOLATOR_H
#include <components/distanceMeasurement/IDistanceMetric.h>

#include "IDynamicInterpolator.h"
#include "components/collisionHandlers/static/IStaticCollisionHandler.h"
#include "components/interpolators/static/IStaticInterpolator.h"
#include "components/interpolators/static/StaticInterpolator.h"


class DynamicInterpolator : public IDynamicInterpolator
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    DynamicInterpolator(std::unique_ptr<IStaticInterpolator> staticInterpolator,double interpolationThreshold) :
        staticInterpolator(std::move(staticInterpolator)), interpolationThreshold(interpolationThreshold) {};

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::DynamicEnv, Capability::MovingTarget}; };

    std::vector<Keyframe> interpolate(const Keyframe &start, const Keyframe &end) override;

    Keyframe getIntermediatePosition(const Keyframe &from, const Keyframe &to, double stepSize) override;

    std::vector<Keyframe> getInterpolatedKeyframesAtRate(const std::vector<Keyframe> &keyframes, int fps) override;

    Keyframe getInterpolatedKeyframeAtTime(const Keyframe &before, const Keyframe &after, double time) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    Keyframe extractKeyframeAtTime(const Animation *animation, double time) override;

protected:
    double interpolationThreshold;
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::unique_ptr<IStaticInterpolator> staticInterpolator;

};



#endif //KEYFRAMEINTERPOLATOR_H
