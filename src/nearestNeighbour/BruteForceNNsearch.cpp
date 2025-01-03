//
// Created by arseniy on 28.10.24.
//

#include "BruteForceNNsearch.h"

int BruteForceNNsearch::findNearestNeighbourIndex(const Pose &pose)
{
    double minDist = std::numeric_limits<double>::max();
    int minIndex = -1;
    for (int i = 0; i < points.size(); i++)
    {
        double distance = distanceMetric->getDistance(points[i], pose);
        if (distance < minDist)
        {
            minDist = distance;
            minIndex = i;
        }
    }
    return minIndex;
}

void BruteForceNNsearch::addPoint(const Pose &pose)
{
    points.push_back(pose);
}
