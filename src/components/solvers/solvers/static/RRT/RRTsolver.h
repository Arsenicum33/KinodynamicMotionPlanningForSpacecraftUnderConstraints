//
// Created by arseniy on 22.10.24.
//

#ifndef RRTSOLVER_H
#define RRTSOLVER_H

#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>

#include "components/pathGenerator/tree/ITreePathGenerator.h"
#include "components/sampling/pose/IPoseSampler.h"
#include "components/solvers/solvers/ARRTsolver.h"
#include "components/solvers/solvers/static/IStaticSolver.h"
#include "components/solvers/treeUtils/ATreeSolver.h"

class RRTsolver : public ARRTsolver<Pose, Pose>, public IStaticSolver
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    RRTsolver(int maxIterations, double maxStepSize) : ARRTsolver(maxIterations, maxStepSize) {}

    std::vector<Pose> solve(const Pose& startPosition, const Pose& goalPosition) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    void build() override;
protected:
    std::shared_ptr<AbstractNearestNeighbourSearch<Pose>> nnSearch;
    std::shared_ptr<IPoseSampler<Pose>> poseSampler;
    std::shared_ptr<ICollisionHandler> collisionHandler;
    std::shared_ptr<ITreePathGenerator<Pose>> pathGenerator;
};



#endif //RRTSOLVER_H
