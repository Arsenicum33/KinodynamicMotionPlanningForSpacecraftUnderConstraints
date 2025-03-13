//
// Created by arseniy on 10.3.25.
//

#ifndef ITOTALDISTANCEMETRIC_H
#define ITOTALDISTANCEMETRIC_H
#include <components/distanceMeasurement/IDistanceMetric.h>


template <typename T>
class ITotalDistanceMetric : public IDistanceMetric
{
public:
    virtual double getTotalDistance(const T& pos1, const T& pos2) = 0;
};
#endif //ITOTALDISTANCEMETRIC_H
