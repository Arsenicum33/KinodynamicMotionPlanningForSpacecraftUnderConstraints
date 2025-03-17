//
// Created by arseniy on 14.3.25.
//

#ifndef KEYFRAMEINTERPOLATOR_H
#define KEYFRAMEINTERPOLATOR_H
#include <components/distanceMeasurement/IDistanceMetric.h>

#include "IKeyframeInterpolator.h"
#include "components/interpolators/pose/IPoseInterpolator.h"
#include "components/interpolators/pose/PoseInterpolator.h"


class KeyframeInterpolator : public IKeyframeInterpolator
{
public:
    KeyframeInterpolator(double interpolationThreshold) : interpolationThreshold(interpolationThreshold),
        poseInterpolator(interpolationThreshold){};
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::DynamicEnv, Capability::MovingTarget}; };

    std::vector<Keyframe> interpolate(const Keyframe &start, const Keyframe &end) override;

    Keyframe getIntermediatePosition(const Keyframe &from, const Keyframe &to, double stepSize) override;

    std::vector<Keyframe> getInterpolatedKeyframesAtRate(const std::vector<Keyframe> &keyframes, int fps) override;

    Keyframe getInterpolatedKeyframeAtTime(const Keyframe &before, const Keyframe &after, double time) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    Keyframe extractKeyframeAtTime(DynamicObject<RAPID_model> *dynamicObject, double time) override;

protected:
    double interpolationThreshold;
    std::shared_ptr<IDistanceMetric> distanceMetric;

private:
    PoseInterpolator poseInterpolator;
};



#endif //KEYFRAMEINTERPOLATOR_H
