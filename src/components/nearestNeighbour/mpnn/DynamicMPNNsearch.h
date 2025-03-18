//
// Created by arseniy on 18.3.25.
//

#ifndef DYNAMICMPNNSEARCH_H
#define DYNAMICMPNNSEARCH_H
#include "AMPNNsearch.h"


class DynamicMPNNsearch : public AMPNNsearch<Keyframe>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    explicit DynamicMPNNsearch(int maxNeighbours)
        : AMPNNsearch<Keyframe>(maxNeighbours) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv}; };
};



#endif //DYNAMICMPNNSEARCH_H
