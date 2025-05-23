// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef RRTSOLVER_H
#define RRTSOLVER_H
#include "components/solvers/RRT/AGeometricRRTsolver.h"


class RRTsolver : public AGeometricRRTsolver<Pose, Pose, Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    RRTsolver(int maxIterations, double maxStepSize, int outputPeriod) : AGeometricRRTsolver(maxIterations, maxStepSize, outputPeriod) {}
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv };}
};



#endif //RRTSOLVER_H
