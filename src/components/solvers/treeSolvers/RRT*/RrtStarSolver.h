//
// Created by arseniy on 12.10.24.
//

#ifndef RRTSTARSOLVER_H
#define RRTSTARSOLVER_H
#include "../AbstractTreeSolver.h"
#include "../../configs/treeSolverConfigs/RRT*/RrtStarSolverConfig.h"
#include "../../../distanceMeasurement/IDistanceMetric.h"
#include "../../../collisionHandlers/ICollisionHandler.h"
#include "../../../../poses/static/sampling/IPoseSampler.h"
#include "../../../nearestNeighbour/AbstractNearestNeighbourSearch.h"
#include "../../../../poses/static/PoseMath.h"
#include "../Tree.h"

class RrtStarSolver : public AbstractTreeSolver<RrtStarSolverConfig>
{
public:
    RrtStarSolver(const RrtStarSolverConfig& config,  const EnvSettings& envSettings):
        AbstractTreeSolver(config, envSettings) {}
    std::vector<Pose> solve(const Pose& startPosition, const Pose& goalPosition) override;
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; };

    void resolveDependencies(ComponentConfig &config, ComponentManager *manager) override;
private:
    int findMinCostParent(const Pose& pose, std::vector<int>& collisionFreeNeighboursIndexes);



private:
    std::shared_ptr<AbstractNearestNeighbourSearch> nnSearch;
    std::shared_ptr<IPoseSampler> poseSampler;
    std::shared_ptr<ICollisionHandler> collisionHandler;
};



#endif //RRTSTARSOLVER_H
