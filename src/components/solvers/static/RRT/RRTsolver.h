//
// Created by arseniy on 17.3.25.
//

#ifndef RRTSOLVER_H
#define RRTSOLVER_H
#include "components/solvers/AGeometricRRTsolver.h"


class RRTsolver : public AGeometricRRTsolver<Pose, Pose, Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    RRTsolver(int maxIterations, double maxStepSize, int outputPeriod) : AGeometricRRTsolver(maxIterations, maxStepSize, outputPeriod) {}
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv };}
};



#endif //RRTSOLVER_H
