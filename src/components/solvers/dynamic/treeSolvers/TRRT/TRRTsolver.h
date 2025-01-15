//
// Created by arseniy on 14.1.25.
//

#ifndef TRRTSOLVER_H
#define TRRTSOLVER_H
#include <components/collisionHandlers/ICollisionHandler.h>
#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>
#include <poses/static/sampling/IPoseSampler.h>

#include "components/collisionHandlers/dynamic/IDynamicCollisionHandler.h"
#include "components/costFunctions/ICostFunction.h"
#include "components/solvers/dynamic/configs/treeSolvers/TRRT/TRRTsolverConfig.h"
#include "components/solvers/dynamic/treeSolvers/IDynamicTreeSolver.h"


class TRRTsolver : public IDynamicTreeSolver<TRRTsolverConfig>
{
public:
    std::vector<Keyframe> solve(const Pose& startPosition, const Pose& goalPosition) override;
    TRRTsolver(const TRRTsolverConfig& config,  const EnvSettings& envSettings) :
        IDynamicTreeSolver<TRRTsolverConfig>(config, envSettings) {}

    void resolveDependencies(ComponentConfig &config, ComponentManager *manager) override;

private:
    std::shared_ptr<AbstractNearestNeighbourSearch> nnSearch;
    std::shared_ptr<IPoseSampler> poseSampler;
    std::shared_ptr<IDynamicCollisionHandler> collisionHandler;
   // std::shared_ptr<ICostFunction<Keyframe>> costFunction;
};



#endif //TRRTSOLVER_H
