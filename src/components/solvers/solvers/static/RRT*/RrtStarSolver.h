//
// Created by arseniy on 12.10.24.
//

#ifndef RRTSTARSOLVER_H
#define RRTSTARSOLVER_H
#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>

#include "components/sampling/IPoseSampler.h"
#include "components/solvers/solverConfigs/static/RRT*/RrtStarSolverConfig.h"
#include "components/solvers/solvers/static/IStaticSolver.h"
#include "components/solvers/treeUtils/ATreeSolver.h"


class RrtStarSolver : public ATreeSolver<RrtStarSolverConfig, Pose, Pose>, public IStaticSolver
{
public:
    RrtStarSolver(const RrtStarSolverConfig& config,  const EnvSettings& envSettings):
        ATreeSolver(config, envSettings) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    std::vector<Pose> solve(const Pose &startPosition, const Pose &goalPosition) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;
private:
    int findMinCostParent(const Pose& pose, std::vector<int>& collisionFreeNeighboursIndexes);


private:
    std::shared_ptr<AbstractNearestNeighbourSearch<Pose>> nnSearch;
    std::shared_ptr<IPoseSampler<Pose>> poseSampler;
    std::shared_ptr<ICollisionHandler> collisionHandler;
    std::shared_ptr<ITreePathGenerator<Pose>> pathGenerator;
};



#endif //RRTSTARSOLVER_H
