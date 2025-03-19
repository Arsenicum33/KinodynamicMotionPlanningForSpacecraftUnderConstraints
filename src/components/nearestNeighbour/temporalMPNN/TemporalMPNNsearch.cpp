//
// Created by arseniy on 10.3.25.
//

#include "TemporalMPNNsearch.h"

#include <spdlog/spdlog.h>

std::unique_ptr<IComponent> TemporalMPNNsearch::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxNeightbours = std::any_cast<double>(configMap.at("maxNeighbours"));

    return std::make_unique<TemporalMPNNsearch>(maxNeightbours);
}

int TemporalMPNNsearch::findNearestNeighbourIndex(const Keyframe &keyframe)
{
    int idx;
    MPNN::ANNpoint query = MPNN::annAllocPt(dimensions);
    std::vector<double> queryAsVector = keyframe.flatten();
    for (int i=0;i<dimensions;i++)
        query[i] = queryAsVector[i];
    double dann = INFINITY;
    int nearest=-1;
    nearest = (int)kdTree->NearestNeighbor(query,idx,dann);
    MPNN::annDeallocPt(query);
    return nearest;
}

std::vector<int> TemporalMPNNsearch::findKnearestNeighboursIndexes(const Keyframe &keyframe)
{
    std::vector<int> bestIdx(maxNeighbours, -1);
    int* bestIdxData = bestIdx.data();
    int *bestIIdx = new int[maxNeighbours];
    MPNN::ANNpoint bestDist = MPNN::annAllocPt(maxNeighbours);

    MPNN::ANNpoint query = MPNN::annAllocPt(dimensions);
    std::vector<double> queryAsVector = keyframe.flatten();
    for (int i=0;i<dimensions;i++)
        query[i] = queryAsVector[i];
    kdTree->NearestNeighbor(query,bestDist, bestIdxData, bestIIdx);
    MPNN::annDeallocPt(query);
    MPNN::annDeallocPt(bestDist);
    delete[] bestIIdx;
    return bestIdx;
}

void TemporalMPNNsearch::addPoint(const Keyframe &keyframe)
{
    std::vector<double> tmp = keyframe.flattenNoRot();
    if (tmp.size() != dimensions)
    {
        spdlog::error("TemporalMPNNsearch::addPoint number of weights not equal to number of dimensions");
        throw std::runtime_error("TemporalMPNNsearch::addPoint number of weights not equal to number of dimensions");
    }
    MPNN::ANNpoint point = MPNN::annAllocPt(dimensions);
    for (int i = 0; i < dimensions; i++)
        point[i] = tmp[i];
    kdTree->AddPoint(point, indexCounter);
    indexCounter++;
    data.push_back(tmp);
    MPNN::annDeallocPt(point);
}

void TemporalMPNNsearch::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    this->distanceMetric = std::dynamic_pointer_cast<ITotalDistanceMetric<Keyframe>>(manager->getComponent(ComponentType::DistanceMetric));
    AbstractNearestNeighbourSearch::resolveDependencies(config, manager);
}

void TemporalMPNNsearch::build()
{
    if (maxNeighbours > 16)
        throw std::invalid_argument("maxNeighbours > 16");
    topology = std::vector<int>(dimensions, 1);
    MPNN::ANNcoord *scale = new MPNN::ANNcoord[dimensions];
    for(int i=0;i<dimensions;i++)
        scale[i] = 0.0;
    auto weights = distanceMetric->getDimensionWeightsNoRotation();
    if (weights.size() != dimensions)
    {
        spdlog::error("TemporalMPNNsearch::build number of weights not equal to number of dimensions");
        throw std::runtime_error("TemporalMPNNsearch::build number of weights not equal to number of dimensions");
    }
    for(int i=0;i<weights.size();i++)
        scale[i] = weights[i];

    kdTree = new MPNN::MultiANN<int>(dimensions,maxNeighbours,topology.data(),(MPNN::ANNpoint)scale);
}
