//
// Created by arseniy on 10.3.25.
//

#ifndef TEMPORALMPNNSEARCH_H
#define TEMPORALMPNNSEARCH_H
#include <multiann.h>
#include <components/distanceMeasurement/IDistanceMetric.h>
#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>

#include "components/distanceMeasurement/temporalTotal/ITotalDistanceMetric.h"

//TODO rewrite this class to make it inherit AMPNNsearch
class TemporalMPNNsearch : public AbstractNearestNeighbourSearch<Keyframe>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    TemporalMPNNsearch(int maxNeighbours) : maxNeighbours(maxNeighbours) {};

    CapabilitySet getCapabilities() const override {return CapabilitySet {Capability::StaticEnv, Capability::DynamicEnv,
        Capability::MovingTarget, Capability::KinodynamicEnv}; };

    int findNearestNeighbourIndex(const Keyframe &keyframe) override;

    std::vector<int> findKnearestNeighboursIndexes(const Keyframe &keyframe) override;

    void addPoint(const Keyframe &keyframe) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    void build() override;
private:
    std::shared_ptr<ITotalDistanceMetric<Keyframe>> distanceMetric;
    std::vector<int> topology;
    const int dimensions = 3;
    int maxNeighbours;
    int indexCounter=0;
    MPNN::MultiANN<int> *kdTree;
    std::vector<std::vector<double>> data;
};



#endif //TEMPORALMPNNSEARCH_H
