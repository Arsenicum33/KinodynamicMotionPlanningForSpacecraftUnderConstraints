//
// Created by arseniy on 28.10.24.
//

#ifndef BRUTEFORCENNSEARCH_H
#define BRUTEFORCENNSEARCH_H
#include "AbstractNearestNeighbourSearch.h"
#include "../distanceMeasurement /IDistanceMetric.h"
#include "../poses/PoseMath.h"

class BruteForceNNsearch : public AbstractNearestNeighbourSearch
{
public:
    BruteForceNNsearch(std::shared_ptr<IDistanceMetric> distanceMetric) : distanceMetric(distanceMetric) {}
    std::shared_ptr<TreeNode> findNearestNeighbour(const Pose &pose, const std::vector<std::shared_ptr<TreeNode>> &nodes) override;
private:
    std::shared_ptr<IDistanceMetric> distanceMetric;
};



#endif //BRUTEFORCENNSEARCH_H
