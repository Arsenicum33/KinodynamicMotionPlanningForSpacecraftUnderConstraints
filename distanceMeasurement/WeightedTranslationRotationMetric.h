//
// Created by arseniy on 28.10.24.
//

#ifndef WEIGHTEDTRANSLATIONROTATIONMETRIC_H
#define WEIGHTEDTRANSLATIONROTATIONMETRIC_H
#include "IDistanceMetric.h"
#include "../poses/PoseMath.h"

class WeightedTranslationRotationMetric : public IDistanceMetric
{
public:
    WeightedTranslationRotationMetric(double rotationScalingFactor) : rotationScalingFactor(rotationScalingFactor) {}
    double getDistance(const Pose &pose1, const Pose &pose2) override;

private:
    const double rotationScalingFactor;
};



#endif //WEIGHTEDTRANSLATIONROTATIONMETRIC_H
