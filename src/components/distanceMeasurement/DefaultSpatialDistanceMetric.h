//
// Created by arseniy on 28.10.24.
//

#ifndef WEIGHTEDTRANSLATIONROTATIONMETRIC_H
#define WEIGHTEDTRANSLATIONROTATIONMETRIC_H
#include "IDistanceMetric.h"
#include "../../poses/static/PoseMath.h"

class DefaultSpatialDistanceMetric : public IDistanceMetric
{
public:
    DefaultSpatialDistanceMetric(double rotationScalingFactor) : rotationScalingFactor(rotationScalingFactor) {}
    double getSpatialDistance(const Pose &pose1, const Pose &pose2) override;

    std::vector<double> getDimensionWeights() const override;

    std::vector<double> getDimensionWeightsNoRotation() const override;

protected:
    const double rotationScalingFactor;
};



#endif //WEIGHTEDTRANSLATIONROTATIONMETRIC_H
