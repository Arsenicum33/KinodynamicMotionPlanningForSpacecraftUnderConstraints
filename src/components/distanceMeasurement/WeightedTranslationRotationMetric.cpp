//
// Created by arseniy on 28.10.24.
//

#include "WeightedTranslationRotationMetric.h"

double WeightedTranslationRotationMetric::getDistance(const Pose &pose1, const Pose &pose2)
{
    const std::array<double, 3>& t1 = pose1.translation;
    const std::array<double, 3>& t2 = pose2.translation;
    double dx = t2[0] - t1[0];
    double dy = t2[1] - t1[1];
    double dz = t2[2] - t1[2];

    Eigen::Quaterniond quaternion1 = PoseMath::rotationMatrixToQuaternion(pose1.rotation);
    Eigen::Quaterniond quaternion2 = PoseMath::rotationMatrixToQuaternion(pose2.rotation);
    double angle = 2 * acos(std::abs(quaternion1.dot(quaternion2)));

    double euclidianDistance = std::sqrt(dx * dx + dy * dy + dz * dz);
    double rotationDistance = angle * rotationScalingFactor;

    return euclidianDistance + rotationDistance;
}

std::vector<double> WeightedTranslationRotationMetric::getDimensionWeights() const
{
    return std::vector{1.0, 1.0, 1.0, rotationScalingFactor, rotationScalingFactor, rotationScalingFactor};
}

void WeightedTranslationRotationMetric::resolveDependencies(ComponentConfig &config, ComponentManager *manager)
{
    return;
}
