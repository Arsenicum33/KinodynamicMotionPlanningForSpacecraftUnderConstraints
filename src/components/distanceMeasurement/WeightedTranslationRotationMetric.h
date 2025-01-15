//
// Created by arseniy on 28.10.24.
//

#ifndef WEIGHTEDTRANSLATIONROTATIONMETRIC_H
#define WEIGHTEDTRANSLATIONROTATIONMETRIC_H
#include "IDistanceMetric.h"
#include "../../poses/static/PoseMath.h"

class WeightedTranslationRotationMetric : public IDistanceMetric
{
public:
    WeightedTranslationRotationMetric(double rotationScalingFactor) : rotationScalingFactor(rotationScalingFactor) {}
    double getDistance(const Pose &pose1, const Pose &pose2) override;

    std::vector<double> getDimensionWeights() const override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }


private:
    const double rotationScalingFactor;
};



#endif //WEIGHTEDTRANSLATIONROTATIONMETRIC_H
