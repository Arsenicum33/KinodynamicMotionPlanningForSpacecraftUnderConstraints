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

template <typename StoredType, typename SearchedType>
class AMPNNsearch : public IMPNNsearch<StoredType, SearchedType>
{
public:
    AMPNNsearch(int maxNeighbours) : maxNeighbours(maxNeighbours) {}


    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    void build() override;

    std::shared_ptr<StoredType> findNearest(const SearchedType &state) override;

    void add(std::shared_ptr<StoredType> state) override;
private:
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::vector<int> topology;
    const int dimensions = 3;
    int maxNeighbours;
    MPNN::MultiANN<std::shared_ptr<StoredType>> *kdTree;
};

template<typename StoredType, typename SearchedType>
std::shared_ptr<StoredType> AMPNNsearch<StoredType, SearchedType>::findNearest(const SearchedType &state)
{
    int idx;
    MPNN::ANNpoint query = MPNN::annAllocPt(dimensions);
    std::vector<double> queryAsVector = state.flatten();
    for (int i=0;i<dimensions;i++)
        query[i] = queryAsVector[i];
    double dann = INFINITY;
    std::shared_ptr<StoredType> nearest;
    nearest = kdTree->NearestNeighbor(query,idx,dann);
    MPNN::annDeallocPt(query);
    return nearest;
}

template<typename StoredType, typename SearchedType>
void AMPNNsearch<StoredType, SearchedType>::add(std::shared_ptr<StoredType> node)
{

    std::vector<double> tmp = node->pose.flatten();
    MPNN::ANNpoint point = MPNN::annAllocPt(dimensions);
    for (int i = 0; i < dimensions; i++)
        point[i] = tmp[i];
    kdTree->AddPoint(point, node);
    MPNN::annDeallocPt(point);
}


template<typename StoredType, typename SearchedType>
void AMPNNsearch<StoredType, SearchedType>::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IMPNNsearch<StoredType, SearchedType>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}

template<typename StoredType, typename SearchedType>
void AMPNNsearch<StoredType, SearchedType>::build()
{
    IMPNNsearch<StoredType, SearchedType>::build();
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

    kdTree = new MPNN::MultiANN<std::shared_ptr<StoredType>>(dimensions,maxNeighbours,topology.data(),(MPNN::ANNpoint)scale);
}


#endif //MPNNSEARCH_H
