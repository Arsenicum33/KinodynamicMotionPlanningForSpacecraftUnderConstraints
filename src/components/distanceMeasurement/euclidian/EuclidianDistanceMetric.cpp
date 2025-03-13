//
// Created by arseniy on 28.10.24.
//

#include "EuclidianDistanceMetric.h"

double EuclidianDistanceMetric::getSpatialDistance(const Pose &pose1, const Pose &pose2)
{
    const std::array<double, 3>& t1 = pose1.translation;
    const std::array<double, 3>& t2 = pose2.translation;

    double dx = t2[0] - t1[0];
    double dy = t2[1] - t1[1];
    double dz = t2[2] - t1[2];

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::vector<double> EuclidianDistanceMetric::getDimensionWeights() const
{
    return std::vector{ 1.0, 1.0, 1.0};
}
