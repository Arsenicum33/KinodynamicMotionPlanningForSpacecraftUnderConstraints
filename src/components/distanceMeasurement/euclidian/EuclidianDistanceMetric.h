//
// Created by arseniy on 28.10.24.
//

#ifndef EUCLIDIANDISTANCEMETRIC_H
#define EUCLIDIANDISTANCEMETRIC_H
#include "components/distanceMeasurement/IDistanceMetric.h"


class EuclidianDistanceMetric : public IDistanceMetric
{
public:
    double getSpatialDistance(const Pose &pose1, const Pose &pose2) override;

    std::vector<double> getDimensionWeights() const override;
};



#endif //EUCLIDIANDISTANCEMETRIC_H
