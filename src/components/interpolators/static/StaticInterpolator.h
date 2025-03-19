//
// Created by arseniy on 14.3.25.
//

#ifndef POSEINTERPOLATOR_H
#define POSEINTERPOLATOR_H
#include <components/distanceMeasurement/IDistanceMetric.h>

#include "IStaticInterpolator.h"

class StaticInterpolator : public IStaticInterpolator
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    StaticInterpolator(double interpolationThreshold) : interpolationThreshold(interpolationThreshold) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv }; }

    std::vector<Pose> interpolate(const Pose &start, const Pose &end) override;

    Pose getIntermediatePosition(const Pose &from, const Pose &to, double stepSize) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    double interpolationThreshold;
    std::shared_ptr<IDistanceMetric> distanceMetric;
};

#endif //POSEINTERPOLATOR_H
