// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef WEIGHTEDTRANSLATIONROTATIONMETRIC_H
#define WEIGHTEDTRANSLATIONROTATIONMETRIC_H
#include <components/distanceMeasurement/IDistanceMetric.h>


class DefaultSpatialDistanceMetric : public IDistanceMetric
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    DefaultSpatialDistanceMetric(double rotationScalingFactor) : rotationScalingFactor(rotationScalingFactor) {}

    double getSpatialDistance(const Pose &pose1, const Pose &pose2) override;

    std::vector<double> getDimensionWeights() const override;

    std::vector<double> getDimensionWeightsNoRotation() const override;

protected:

    const double rotationScalingFactor;

};



#endif //WEIGHTEDTRANSLATIONROTATIONMETRIC_H
