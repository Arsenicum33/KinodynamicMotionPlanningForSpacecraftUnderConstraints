//
// Created by arseniy on 28.10.24.
//

#ifndef IDISTANCEMETRIC_H
#define IDISTANCEMETRIC_H
#include "../poses/Pose.h"
class IDistanceMetric
{
public:
    virtual ~IDistanceMetric() = default;
    virtual double getDistance(const Pose& pose1, const Pose& pose2) = 0;
};
#endif //IDISTANCEMETRIC_H
