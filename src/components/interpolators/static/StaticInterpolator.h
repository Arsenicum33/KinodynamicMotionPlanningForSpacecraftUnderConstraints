// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef POSEINTERPOLATOR_H
#define POSEINTERPOLATOR_H
#include <components/distanceMeasurement/IDistanceMetric.h>

#include "components/interpolators/AInterpolator.h"

class StaticInterpolator : public AInterpolator<Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    StaticInterpolator(double interpolationThreshold) : interpolationThreshold(interpolationThreshold) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv }; }

protected:
    int calculateInterpolationSteps(const Pose &from, const Pose &to) override;

    Pose interpolateBetweenPositions(const Pose &start, const Pose &end, double factor) override;

    double interpolationThreshold;

};

#endif //POSEINTERPOLATOR_H
