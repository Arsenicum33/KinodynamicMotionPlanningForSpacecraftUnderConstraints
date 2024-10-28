//
// Created by arseniy on 28.10.24.
//

#include "BruteForceNNsearch.h"

std::shared_ptr<TreeNode> BruteForceNNsearch::findNearestNeighbour(const Pose &pose,
    const std::vector<std::shared_ptr<TreeNode>>& nodes)
{
    double minDist = std::numeric_limits<double>::max();
    int minIndex = -1;
    for (int i = 0; i < nodes.size(); i++)
    {
        double distance = distanceMetric->getDistance(nodes[i]->pose, pose);
        if (distance < minDist)
        {
            minDist = distance;
            minIndex = i;
        }
    }
    return nodes[minIndex];
}
