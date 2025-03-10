//
// Created by arseniy on 7.3.25.
//

#ifndef MT_TARRT_H
#define MT_TARRT_H
#include "IMovingTargetSolver.h"
#include "components/sampling/IKeyframeSampler.h"
#include "components/solvers/solverConfigs/movingTarget/MT_TARRTsolverConfig.h"
#include "components/solvers/solvers/dynamic/TARRT/TARRTsolver.h"
#include "components/terminationConditions/ITerminationCondition.h"


class MT_TARRTsolver : public ATreeSolver<MT_TARRTsolverConfig, Keyframe, Keyframe>, public IMovingTargetSolver
{
public:
    MT_TARRTsolver(const MT_TARRTsolverConfig &config, const EnvSettings &envSettings)
        : ATreeSolver<MT_TARRTsolverConfig, Keyframe, Keyframe>(config, envSettings) {}

    std::vector<Keyframe> solve(const Pose &startPosition, const Animation &target) override;

    CapabilitySet getCapabilities() const override { return CapabilitySet {Capability::StaticEnv, Capability::DynamicEnv, Capability::MovingTarget}; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;
private:
    std::shared_ptr<AbstractNearestNeighbourSearch<Keyframe>> nnSearch;
    std::shared_ptr<IKeyframeSampler<Animation>> sampler;
    std::shared_ptr<IDynamicCollisionHandler> collisionHandler;
    std::shared_ptr<ITreePathGenerator<Keyframe>> pathGenerator;
    std::shared_ptr<ITerminationCondition<Keyframe, Animation>> terminationCondition;
};



#endif //MT_TARRT_H
