// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
