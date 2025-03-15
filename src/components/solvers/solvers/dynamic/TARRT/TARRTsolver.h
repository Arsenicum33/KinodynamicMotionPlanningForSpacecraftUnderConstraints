//
// Created by arseniy on 14.1.25.
//

#ifndef TRRTSOLVER_H
#define TRRTSOLVER_H


#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>
#include "components/collisionHandlers/dynamic/IDynamicCollisionHandler.h"
#include "components/interpolators/keyframe/IKeyframeInterpolator.h"
#include "components/pathGenerator/tree/ITreePathGenerator.h"
#include "components/sampling/pose/IPoseSampler.h"
#include "components/solvers/solvers/ARRTsolver.h"
#include "components/solvers/solvers/dynamic/IDynamicSolver.h"
#include "components/solvers/treeUtils/ATreeSolver.h"
#include "components/terminationConditions/ITerminationCondition.h"


class TARRTsolver : public ARRTsolver<Keyframe, Pose>, public IDynamicSolver
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    TARRTsolver(int maxIterations, double maxStepSize, double velocity) :
        ARRTsolver(maxIterations, maxStepSize), velocity(velocity) {}

    std::vector<Keyframe> solve(const Pose& startPosition, const Pose& goalPosition) override;


    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv}; }

protected:
    double velocity;
    std::shared_ptr<AbstractNearestNeighbourSearch<Pose>> nnSearch;
    std::shared_ptr<IPoseSampler<Pose>> poseSampler;
    std::shared_ptr<IDynamicCollisionHandler> collisionHandler;
    std::shared_ptr<ITreePathGenerator<Keyframe>> pathGenerator;
    std::shared_ptr<IKeyframeInterpolator> interpolator;
    std::shared_ptr<ITerminationCondition<Pose, Pose>> terminationCondition;
};



#endif //TRRTSOLVER_H
