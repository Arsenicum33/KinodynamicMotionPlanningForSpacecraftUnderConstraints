//
// Created by arseniy on 22.10.24.
//

#ifndef RRTSOLVER_H
#define RRTSOLVER_H
#include "../AbstractTreeSolver.h"
#include <random>

#include "../../../distanceMeasurement /IDistanceMetric.h"
#include "../../../nearestNeighbour/AbstractNearestNeighbourSearch.h"
#include "../../../poses/sampling/IPoseSampler.h"
#include "../../configs/treeSolverConfigs/RRT/RRTsolverConfig.h"

class RRTsolver : public AbstractTreeSolver<RRTsolverConfig>
{
public:
    std::vector<Pose> solve(const std::vector<std::unique_ptr<RAPID_model>> &obstacles,
                              const std::unique_ptr<RAPID_model> &agent,
                              Pose startPosition,
                              Pose goalPosition) override;
    RRTsolver(const RRTsolverConfig& config,  const EnvSettings& envSettings,
        std::shared_ptr<IDistanceMetric> distanceMetric, std::unique_ptr<AbstractNearestNeighbourSearch> nearestNeighbourSearch,
        std::unique_ptr<IPoseSampler> poseSampler) :
        AbstractTreeSolver(config, envSettings), distanceMetric(std::move(distanceMetric))
        ,nnSearch(std::move(nearestNeighbourSearch)), poseSampler(std::move(poseSampler)) {}
private:
    void initializeTree(Pose& startPosition);


    bool isPathCollisionFree(const Pose& pose1, const Pose& pose2,
                             const std::vector<std::unique_ptr<RAPID_model>> &obstacles,
                             const std::unique_ptr<RAPID_model> &agent) const;
    std::vector<Pose> generatePath(std::shared_ptr<TreeNode> goalNode);

    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::unique_ptr<AbstractNearestNeighbourSearch> nnSearch;
    std::unique_ptr<IPoseSampler> poseSampler;
};



#endif //RRTSOLVER_H
