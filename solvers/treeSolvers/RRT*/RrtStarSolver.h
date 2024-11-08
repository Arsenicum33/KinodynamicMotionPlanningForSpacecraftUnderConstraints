//
// Created by arseniy on 12.10.24.
//

#ifndef RRTSTARSOLVER_H
#define RRTSTARSOLVER_H
#include "../AbstractTreeSolver.h"
#include "../../configs/treeSolverConfigs/RRT*/RrtStarSolverConfig.h"
#include "../../../distanceMeasurement/IDistanceMetric.h"
#include "../../../collisionHandlers/ICollisionHandler.h"
#include "../../../poses/sampling/IPoseSampler.h"
#include "../../../nearestNeighbour/AbstractNearestNeighbourSearch.h"
#include "../../../poses/PoseMath.h"
#include "../Tree.h"

class RrtStarSolver : public AbstractTreeSolver<RrtStarSolverConfig>
{
public:
    RrtStarSolver(const RrtStarSolverConfig& config,  const EnvSettings& envSettings,
        std::shared_ptr<IDistanceMetric> distanceMetric, std::unique_ptr<AbstractNearestNeighbourSearch> nearestNeighbourSearch,
        std::unique_ptr<IPoseSampler> poseSampler, std::unique_ptr<ICollisionHandler> collisionHandler) :
        AbstractTreeSolver(config, envSettings, distanceMetric),nnSearch(std::move(nearestNeighbourSearch)),
        poseSampler(std::move(poseSampler)), collisionHandler(std::move(collisionHandler)) {}
    std::vector<Pose> solve(const Pose& startPosition, const Pose& goalPosition) override;
private:
    std::vector<Pose> generatePath(std::shared_ptr<TreeNode> goalNode);
    int findMinCostParent(const Pose& pose, std::vector<int>& collisionFreeNeighboursIndexes);
    std::unique_ptr<AbstractNearestNeighbourSearch> nnSearch;
    std::unique_ptr<IPoseSampler> poseSampler;
    std::shared_ptr<ICollisionHandler> collisionHandler;
};



#endif //RRTSTARSOLVER_H
