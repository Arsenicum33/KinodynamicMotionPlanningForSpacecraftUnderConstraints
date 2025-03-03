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
#include "components/sampling/IPoseSampler.h"
#include "../../configs/treeSolverConfigs/RRT/RRTsolverConfig.h"
#include "../../../../poses/static/PoseMath.h"
class RRTsolver : public AbstractTreeSolver<RRTsolverConfig>
{
public:
    std::vector<Pose> solve(const Pose& startPosition, const Pose& goalPosition) override;
    RRTsolver(const RRTsolverConfig& config,  const EnvSettings& envSettings) :
        AbstractTreeSolver(config, envSettings) {}


    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    void build() override;
private:
    std::shared_ptr<AbstractNearestNeighbourSearch> nnSearch;
    std::shared_ptr<IPoseSampler> poseSampler;
    std::shared_ptr<ICollisionHandler> collisionHandler;
};



#endif //RRTSOLVER_H
