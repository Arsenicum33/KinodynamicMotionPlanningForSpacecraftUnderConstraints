//
// Created by arseniy on 28.10.24.
//

#ifndef IDISTANCEMETRIC_H
#define IDISTANCEMETRIC_H
#include "../../poses/static/Pose.h"
#include "../IComponent.h"

class IDistanceMetric : public IComponent
{
public:
    virtual double getDistance(const Pose& pose1, const Pose& pose2) = 0;
    virtual std::vector<double> getDimensionWeights() const = 0;
};
#endif //IDISTANCEMETRIC_H
