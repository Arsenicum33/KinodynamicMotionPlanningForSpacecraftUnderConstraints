//
// Created by arseniy on 14.1.25.
//

#ifndef TRRTSOLVER_H
#define TRRTSOLVER_H


#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>
#include <components/sampling/IPoseSampler.h>
#include "components/collisionHandlers/dynamic/IDynamicCollisionHandler.h"
#include "components/pathGenerator/ITreePathGenerator.h"
#include "components/solvers/solverConfigs/dynamic/TARRT/TARRTsolverConfig.h"
#include "components/solvers/solvers/dynamic/IDynamicSolver.h"
#include "components/solvers/treeUtils/ATreeSolver.h"


class TARRTsolver : public ATreeSolver<TARRTsolverConfig, Keyframe>, public IDynamicSolver
{
public:
    std::vector<Keyframe> solve(const Pose& startPosition, const Pose& goalPosition) override;
    TARRTsolver(const TARRTsolverConfig& config,  const EnvSettings& envSettings) :
        ATreeSolver(config, envSettings) {}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv}; }

private:
    std::shared_ptr<AbstractNearestNeighbourSearch> nnSearch;
    std::shared_ptr<IPoseSampler> poseSampler;
    std::shared_ptr<IDynamicCollisionHandler> collisionHandler;
    std::shared_ptr<ITreePathGenerator<Keyframe>> pathGenerator;
};



#endif //TRRTSOLVER_H
