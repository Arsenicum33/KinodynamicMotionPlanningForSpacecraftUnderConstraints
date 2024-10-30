//
// Created by arseniy on 28.10.24.
//

#ifndef MPNNSEARCH_H
#define MPNNSEARCH_H
#include "AbstractNearestNeighbourSearch.h"
#include "../distanceMeasurement/IDistanceMetric.h"
#include "../mpnn/kd_tree.h"

class MPNNsearch : AbstractNearestNeighbourSearch
{
public:
    MPNNsearch(std::shared_ptr<IDistanceMetric> distanceMetric) : distanceMetric(distanceMetric) {};
    std::shared_ptr<TreeNode> findNearestNeighbour(const Pose &pose,
        const std::vector<std::shared_ptr<TreeNode>> &nodes) override;

private:
    std::shared_ptr<IDistanceMetric> distanceMetric;
};



#endif //MPNNSEARCH_H
