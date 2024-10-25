//
// Created by arseniy on 22.10.24.
//

#ifndef RRTSOLVER_H
#define RRTSOLVER_H
#include "../AbstractTreeSolver.h"
#include <random>

#include "../../configs/treeSolverConfigs/RRT/RRTsolverConfig.h"

class RRTsolver : public AbstractTreeSolver<RRTsolverConfig>
{
public:
    std::vector<Pose> solve(const std::vector<std::unique_ptr<RAPID_model>> &obstacles,
                              const std::unique_ptr<RAPID_model> &agent,
                              Pose startPosition,
                              Pose goalPosition) override;
    RRTsolver(const RRTsolverConfig& config,  const EnvSettings& envSettings)
        : AbstractTreeSolver(config, envSettings), gen(std::random_device{}()) {}
private:
    void initializeTree(Pose& startPosition);
    Pose sampleRandomPose(Pose& goalPosition);
    std::shared_ptr<TreeNode> findNearestNeighbour(Pose& pose);
    Pose getPoseWithinStepSize(const Pose& from, const Pose& to) const;
    double getDistance(const Pose& pose1, const Pose& pose2) const;
    bool isPathCollisionFree(const Pose& pose1, const Pose& pose2,
                             const std::vector<std::unique_ptr<RAPID_model>> &obstacles,
                             const std::unique_ptr<RAPID_model> &agent) const;
    std::vector<Pose> generatePath(std::shared_ptr<TreeNode> goalNode);

    std::mt19937 gen;
};



#endif //RRTSOLVER_H
