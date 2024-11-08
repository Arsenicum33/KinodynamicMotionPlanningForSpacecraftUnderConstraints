//
// Created by arseniy on 28.10.24.
//

#ifndef BRUTEFORCENNSEARCH_H
#define BRUTEFORCENNSEARCH_H
#include "AbstractNearestNeighbourSearch.h"
#include "../distanceMeasurement/IDistanceMetric.h"
#include "../poses/PoseMath.h"

class BruteForceNNsearch : public AbstractNearestNeighbourSearch
{
public:
    BruteForceNNsearch(std::shared_ptr<IDistanceMetric> distanceMetric) : distanceMetric(distanceMetric) {}
    int findNearestNeighbourIndex(const Pose &pose) override;

    void addPoint(const Pose &pose) override;

private:
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::vector<Pose> points;
};



#endif //BRUTEFORCENNSEARCH_H
