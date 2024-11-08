//
// Created by arseniy on 22.10.24.
//

#ifndef RRTSOLVER_H
#define RRTSOLVER_H
#include "../AbstractTreeSolver.h"
#include <random>

#include "../../../collisionHandlers/ICollisionHandler.h"
#include "../../../distanceMeasurement/IDistanceMetric.h"
#include "../../../nearestNeighbour/AbstractNearestNeighbourSearch.h"
#include "../../../poses/sampling/IPoseSampler.h"
#include "../../configs/treeSolverConfigs/RRT/RRTsolverConfig.h"
#include "../../../poses/PoseMath.h"
class RRTsolver : public AbstractTreeSolver<RRTsolverConfig>
{
public:
    std::vector<Pose> solve(const Pose& startPosition, const Pose& goalPosition) override;
    RRTsolver(const RRTsolverConfig& config,  const EnvSettings& envSettings,
        std::shared_ptr<IDistanceMetric> distanceMetric, std::unique_ptr<AbstractNearestNeighbourSearch> nearestNeighbourSearch,
        std::unique_ptr<IPoseSampler> poseSampler, std::unique_ptr<ICollisionHandler> collisionHandler) :
        AbstractTreeSolver(config, envSettings, distanceMetric),nnSearch(std::move(nearestNeighbourSearch)),
        poseSampler(std::move(poseSampler)), collisionHandler(std::move(collisionHandler)) {}
private:

    std::vector<Pose> generatePath(std::shared_ptr<TreeNode> goalNode);
    std::unique_ptr<AbstractNearestNeighbourSearch> nnSearch;
    std::unique_ptr<IPoseSampler> poseSampler;
    std::unique_ptr<ICollisionHandler> collisionHandler;
};



#endif //RRTSOLVER_H
