// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "DefaultSpatialDistanceMetric.h"

#include <dto/poses/static/poseMath/PoseMath.h>


std::unique_ptr<IComponent> DefaultSpatialDistanceMetric::createComponent(const ComponentConfig &config,
                                                                          const ReaderContext &context)
{
    const auto& configMap = config.config;

    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));

    return std::make_unique<DefaultSpatialDistanceMetric>(rotationScalingFactor);
}

double DefaultSpatialDistanceMetric::getSpatialDistance(const Pose &pose1, const Pose &pose2)
{
    const std::array<double, 3>& t1 = pose1.translation;
    const std::array<double, 3>& t2 = pose2.translation;
    double dx = t2[0] - t1[0];
    double dy = t2[1] - t1[1];
    double dz = t2[2] - t1[2];

    double angle = 2 * acos(std::abs(pose1.rotation.dot(pose2.rotation)));

    double euclidianDistance = std::sqrt(dx * dx + dy * dy + dz * dz);
    double rotationDistance = angle * rotationScalingFactor;

    return euclidianDistance + rotationDistance;
}


std::vector<double> DefaultSpatialDistanceMetric::getDimensionWeights() const
{
    return std::vector{1.0, 1.0, 1.0, rotationScalingFactor, rotationScalingFactor, rotationScalingFactor};
}

std::vector<double> DefaultSpatialDistanceMetric::getDimensionWeightsNoRotation() const
{
    return std::vector{1.0, 1.0, 1.0};
}
