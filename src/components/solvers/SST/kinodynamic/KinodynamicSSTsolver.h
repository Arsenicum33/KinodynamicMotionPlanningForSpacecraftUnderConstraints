// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef KINODYNAMICSSTSOLVER_H
#define KINODYNAMICSSTSOLVER_H
#include "components/solvers/SST/ASSTsolver.h"


class KinodynamicSSTsolver : public ASSTsolver<State, Animation>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    KinodynamicSSTsolver(int maxIterations, double selectionRadius, double maxWitnessProximityRadius)
    : ASSTsolver<State, Animation>(
        maxIterations, selectionRadius, maxWitnessProximityRadius)
    {}
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv};};
};



#endif //KINODYNAMICSSTSOLVER_H
