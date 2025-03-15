//
// Created by arseniy on 7.3.25.
//

#ifndef MT_TARRT_H
#define MT_TARRT_H
#include "IMovingTargetSolver.h"
#include "components/interpolators/keyframe/IKeyframeInterpolator.h"
#include "components/sampling/keyframe/IKeyframeSampler.h"
#include "components/solvers/solvers/dynamic/TARRT/TARRTsolver.h"
#include "components/terminationConditions/ITerminationCondition.h"


class MT_TARRTsolver : public ARRTsolver<Keyframe, Keyframe>, public IMovingTargetSolver
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    MT_TARRTsolver(int maxIterations, double maxStepSize, double velocity) :
        ARRTsolver(maxIterations, maxStepSize), velocity(velocity) {}

    std::vector<Keyframe> solve(const Pose &startPosition, const Animation &target) override;

    CapabilitySet getCapabilities() const override { return CapabilitySet {Capability::StaticEnv, Capability::DynamicEnv, Capability::MovingTarget}; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;
protected:
    double velocity;

    std::shared_ptr<AbstractNearestNeighbourSearch<Keyframe>> nnSearch;
    std::shared_ptr<IKeyframeSampler<Animation>> sampler;
    std::shared_ptr<IDynamicCollisionHandler> collisionHandler;
    std::shared_ptr<ITreePathGenerator<Keyframe>> pathGenerator;
    std::shared_ptr<ITerminationCondition<Keyframe, Animation>> terminationCondition;
    std::shared_ptr<IKeyframeInterpolator> interpolator;
};



#endif //MT_TARRT_H
