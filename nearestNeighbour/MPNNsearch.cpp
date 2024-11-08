//
// Created by arseniy on 28.10.24.
//

#include "MPNNsearch.h"

MPNNsearch::MPNNsearch(std::shared_ptr<IDistanceMetric> distanceMetric, int dimensions, int maxNeighbours) :
    distanceMetric(distanceMetric), dimensions(dimensions), maxNeighbours(maxNeighbours)
{
    if (maxNeighbours > 16)
        throw std::invalid_argument("maxNeighbours > 16");
    topology = std::vector<int>(dimensions, 1);
    MPNN::ANNcoord *scale = new MPNN::ANNcoord[dimensions];
    for(int i=0;i<dimensions;i++)
        scale[i] = 0.0;
    auto weights = distanceMetric->getDimensionWeights();
    for(int i=0;i<weights.size();i++)
        scale[i] = weights[i];

    kdTree = new MPNN::MultiANN<int>(dimensions,maxNeighbours,topology.data(),(MPNN::ANNpoint)scale);


}

int MPNNsearch::findNearestNeighbourIndex(const Pose &pose)
{
    int idx;
    MPNN::ANNpoint query = MPNN::annAllocPt(dimensions);
    std::vector<double> queryAsVector = pose.flatten();
    for (int i=0;i<dimensions;i++)
        query[i] = queryAsVector[i];
    double dann = INFINITY;
    int nearest=-1;
    nearest = (int)kdTree->NearestNeighbor(query,idx,dann);
    MPNN::annDeallocPt(query);
    return nearest;
}

std::vector<int> MPNNsearch::findKnearestNeighboursIndexes(const Pose &pose)
{
    std::vector<int> bestIdx(maxNeighbours, -1);
    int* bestIdxData = bestIdx.data();
    int *bestIIdx = new int[maxNeighbours];
    MPNN::ANNpoint bestDist = MPNN::annAllocPt(maxNeighbours);

    MPNN::ANNpoint query = MPNN::annAllocPt(dimensions);
    std::vector<double> queryAsVector = pose.flatten();
    for (int i=0;i<dimensions;i++)
        query[i] = queryAsVector[i];
    kdTree->NearestNeighbor(query,bestDist, bestIdxData, bestIIdx);
    MPNN::annDeallocPt(query);
    MPNN::annDeallocPt(bestDist);
    delete[] bestIIdx;
    return bestIdx;
}


void MPNNsearch::addPoint(const Pose &pose)
{
    std::vector<double> tmp = pose.flatten();
    MPNN::ANNpoint point = MPNN::annAllocPt(dimensions);
    for (int i = 0; i < tmp.size(); i++)
        point[i] = tmp[i];
    kdTree->AddPoint(point, indexCounter);
    indexCounter++;
    data.push_back(tmp);
    MPNN::annDeallocPt(point);
}

