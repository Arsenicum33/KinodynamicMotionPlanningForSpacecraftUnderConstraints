//
// Created by arseniy on 18.3.25.
//

#ifndef STATICMPNNSEARCH_H
#define STATICMPNNSEARCH_H
#include "components/nearestNeighbour/mpnn/AMPNNsearch.h"


class StaticMPNNsearch : public AMPNNsearch<Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    explicit StaticMPNNsearch(int maxNeighbours)
        : AMPNNsearch<Pose>(maxNeighbours) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }
};



#endif //STATICMPNNSEARCH_H
