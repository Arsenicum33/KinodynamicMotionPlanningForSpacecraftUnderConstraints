// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef AINTERPOLATOR_H
#define AINTERPOLATOR_H
#include "IInterpolator.h"

template <typename PositionType>
class AInterpolator : public IInterpolator<PositionType>
{
public:
    std::vector<PositionType> interpolate(const PositionType &start, const PositionType &end) override;

    PositionType getIntermediatePosition(const PositionType &from, const PositionType &to, double stepSize) override;

protected:
    virtual int calculateInterpolationSteps(const PositionType &from, const PositionType &to) = 0;
    std::vector<PositionType> interpolateSteps(const PositionType &start, const PositionType &end, int steps);
    virtual PositionType interpolateBetweenPositions(const PositionType &start, const PositionType &end, double factor) = 0;

};

template<typename PositionType>
std::vector<PositionType> AInterpolator<PositionType>::interpolate(const PositionType &start, const PositionType &end)
{
    int numSteps = calculateInterpolationSteps(start, end);
    return interpolateSteps(start, end, numSteps);
}

template<typename PositionType>
PositionType AInterpolator<PositionType>::getIntermediatePosition(const PositionType &from, const PositionType &to,
    double stepSize)
{
    double distance = this->distanceMetric->getSpatialDistance(from, to);
    if (distance <= stepSize)
        return to;
    double factor = stepSize / distance;
    return interpolateBetweenPositions(from, to, factor);
}

template<typename PositionType>
std::vector<PositionType> AInterpolator<PositionType>::interpolateSteps(const PositionType &start,
    const PositionType &end, int numSteps)
{
    if (numSteps <= 1)
    {
        return std::vector<PositionType> { start, end};
    }
    std::vector<PositionType> states;
    for (int k = 0; k <= numSteps; k++)
    {
        double factor = static_cast<double>(k) / static_cast<double>(numSteps);
        PositionType interpolatedState = interpolateBetweenPositions(start, end, factor);
        states.push_back(interpolatedState);
    }
    return states;
}

#endif //AINTERPOLATOR_H
