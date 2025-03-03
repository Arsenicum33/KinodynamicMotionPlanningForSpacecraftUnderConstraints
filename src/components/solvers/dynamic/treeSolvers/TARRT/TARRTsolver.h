//
// Created by arseniy on 14.1.25.
//

#ifndef TRRTSOLVER_H
#define TRRTSOLVER_H
#include <components/collisionHandlers/ICollisionHandler.h>
#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>
#include <components/sampling/IPoseSampler.h>

#include "components/collisionHandlers/dynamic/IDynamicCollisionHandler.h"
#include "components/costFunctions/ICostFunction.h"
#include "components/pathGenerator/ITreePathGenerator.h"
#include "components/solvers/dynamic/configs/treeSolvers/TARRT/TARRTsolverConfig.h"
#include "components/solvers/dynamic/treeSolvers/IDynamicTreeSolver.h"


class TARRTsolver : public IDynamicTreeSolver<TARRTsolverConfig>
{
public:
    std::vector<Keyframe> solve(const Pose& startPosition, const Pose& goalPosition) override;
    TARRTsolver(const TARRTsolverConfig& config,  const EnvSettings& envSettings) :
        IDynamicTreeSolver<TARRTsolverConfig>(config, envSettings) {}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    std::shared_ptr<AbstractNearestNeighbourSearch> nnSearch;
    std::shared_ptr<IPoseSampler> poseSampler;
    std::shared_ptr<IDynamicCollisionHandler> collisionHandler;
    std::shared_ptr<ITreePathGenerator<Keyframe>> pathGenerator;
};



#endif //TRRTSOLVER_H
