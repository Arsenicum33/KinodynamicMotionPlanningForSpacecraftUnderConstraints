// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IDISTANCEMETRIC_H
#define IDISTANCEMETRIC_H


#include <dto/poses/static/pose/Pose.h>

#include "../IComponent.h"

class IDistanceMetric : public IComponent
{
public:
    virtual double getSpatialDistance(const Pose& pose1, const Pose& pose2) = 0;
    virtual std::vector<double> getDimensionWeights() const = 0;
    virtual std::vector<double> getDimensionWeightsNoRotation() const = 0;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv, Capability::MovingTarget}; }

    ComponentType getType() const override { return ComponentType::DistanceMetric; }
};
#endif //IDISTANCEMETRIC_H
