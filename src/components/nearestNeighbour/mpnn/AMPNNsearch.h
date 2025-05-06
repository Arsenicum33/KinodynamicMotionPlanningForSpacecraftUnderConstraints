//
// Created by arseniy on 28.10.24.
//

#ifndef MPNNSEARCH_H
#define MPNNSEARCH_H

#include <components/distanceMeasurement/IDistanceMetric.h>
#include <components/nearestNeighbour/mpnn/IMPNNsearch.h>

#include "../mpnn/kd_tree.h"
#include "../mpnn/multiann.h"
#include "../mpnn/ANN.h"

template <typename PositionType>
class AMPNNsearch : public IMPNNsearch<PositionType>
{
public:
    AMPNNsearch(int maxNeighbours) : maxNeighbours(maxNeighbours) {}

    int findNearestNeighbourIndex(const PositionType &position) override;

    void addPoint(const PositionType &position) override;

    std::vector<int> findKnearestNeighboursIndexes(const PositionType &position) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    void build() override;
private:

    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::vector<int> topology;
    const int dimensions = 3;
    int maxNeighbours;
    int indexCounter=0;
    MPNN::MultiANN<int> *kdTree;
    std::vector<std::vector<double>> data;
};

template<typename PositionType>
int AMPNNsearch<PositionType>::findNearestNeighbourIndex(const PositionType &position)
{
    int idx;
    MPNN::ANNpoint query = MPNN::annAllocPt(dimensions);
    std::vector<double> queryAsVector = position.flatten();
    for (int i=0;i<dimensions;i++)
        query[i] = queryAsVector[i];
    double dann = INFINITY;
    int nearest=-1;
    nearest = (int)kdTree->NearestNeighbor(query,idx,dann);
    MPNN::annDeallocPt(query);
    return nearest;
}

template<typename PositionType>
void AMPNNsearch<PositionType>::addPoint(const PositionType &position)
{
    std::vector<double> tmp = position.flatten();
    MPNN::ANNpoint point = MPNN::annAllocPt(dimensions);
    for (int i = 0; i < dimensions; i++)
        point[i] = tmp[i];
    kdTree->AddPoint(point, indexCounter);
    indexCounter++;
    data.push_back(tmp);
    MPNN::annDeallocPt(point);
}

template<typename PositionType>
std::vector<int> AMPNNsearch<PositionType>::findKnearestNeighboursIndexes(const PositionType &position)
{
    std::vector<int> bestIdx(maxNeighbours, -1);
    int* bestIdxData = bestIdx.data();
    int *bestIIdx = new int[maxNeighbours];
    MPNN::ANNpoint bestDist = MPNN::annAllocPt(maxNeighbours);

    MPNN::ANNpoint query = MPNN::annAllocPt(dimensions);
    std::vector<double> queryAsVector = position.flatten();
    for (int i=0;i<dimensions;i++)
        query[i] = queryAsVector[i];
    kdTree->NearestNeighbor(query,bestDist, bestIdxData, bestIIdx);
    MPNN::annDeallocPt(query);
    MPNN::annDeallocPt(bestDist);
    delete[] bestIIdx;
    return bestIdx;
}

template<typename PositionType>
void AMPNNsearch<PositionType>::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IMPNNsearch<PositionType>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}

template<typename PositionType>
void AMPNNsearch<PositionType>::build()
{
    IMPNNsearch<PositionType>::build();
    if (maxNeighbours > 16)
        throw std::invalid_argument("maxNeighbours > 16");
    topology = std::vector<int>(dimensions, 1);
    MPNN::ANNcoord *scale = new MPNN::ANNcoord[dimensions];
    for(int i=0;i<dimensions;i++)
        scale[i] = 0.0;
    auto weights = distanceMetric->getDimensionWeightsNoRotation();
    if (weights.size() != dimensions)
    {
        spdlog::error("MPNNsearch::build number of weights not equal to number of dimensions");
        throw std::runtime_error("MPNNsearch::build number of weights not equal to number of dimensions");
    }
    for(int i=0;i<weights.size();i++)
        scale[i] = weights[i];

    kdTree = new MPNN::MultiANN<int>(dimensions,maxNeighbours,topology.data(),(MPNN::ANNpoint)scale);
}


#endif //MPNNSEARCH_H
