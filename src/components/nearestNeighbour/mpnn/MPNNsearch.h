//
// Created by arseniy on 28.10.24.
//

#ifndef MPNNSEARCH_H
#define MPNNSEARCH_H

#include <components/distanceMeasurement/IDistanceMetric.h>
#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>

#include "../mpnn/kd_tree.h"
#include "../mpnn/multiann.h"
#include "../mpnn/ANN.h"

class MPNNsearch : public AbstractNearestNeighbourSearch<Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    MPNNsearch(int maxNeighbours) : maxNeighbours(maxNeighbours) {}

    int findNearestNeighbourIndex(const Pose &pose) override;

    void addPoint(const Pose &pose) override;

    std::vector<int> findKnearestNeighboursIndexes(const Pose &pose) override;
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv}; }

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


#endif //MPNNSEARCH_H
