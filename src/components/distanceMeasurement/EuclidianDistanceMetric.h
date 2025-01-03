//
// Created by arseniy on 28.10.24.
//

#ifndef EUCLIDIANDISTANCEMETRIC_H
#define EUCLIDIANDISTANCEMETRIC_H
#include "IDistanceMetric.h"


class EuclidianDistanceMetric : public IDistanceMetric
{
public:
    double getDistance(const Pose &pose1, const Pose &pose2) override;

    std::vector<double> getDimensionWeights() const override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; };
};



#endif //EUCLIDIANDISTANCEMETRIC_H
