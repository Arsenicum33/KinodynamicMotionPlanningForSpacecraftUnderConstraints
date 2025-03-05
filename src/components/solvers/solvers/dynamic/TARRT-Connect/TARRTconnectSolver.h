//
// Created by arseniy on 19.1.25.
//

#ifndef TARRTCONNECTSOLVER_H
#define TARRTCONNECTSOLVER_H
#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>

#include "components/collisionHandlers/dynamic/IDynamicCollisionHandler.h"
#include "components/pathGenerator/ITreeConnectPathGenerator.h"
#include "components/sampling/IPoseSampler.h"
#include "components/solvers/solverConfigs/dynamic/TARRT-Connect/TARRTconnectSolverConfig.h"
#include "components/solvers/solvers/dynamic/IDynamicSolver.h"
#include "components/solvers/treeUtils/ATreeSolver.h"


class TARRTconnectSolver : public ATreeSolver<TARRTconnectSolverConfig, Keyframe>, public IDynamicSolver
{
public:
    std::vector<Keyframe> solve(const Pose& startPosition, const Pose& goalPosition) override;
    TARRTconnectSolver(const TARRTconnectSolverConfig& config,  const EnvSettings& envSettings) :
        ATreeSolver(config, envSettings) {}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    void build() override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv}; }

private:
    std::shared_ptr<TreeNode<Keyframe>> tryExtendTree(Tree<Keyframe> * tree, AbstractNearestNeighbourSearch* NNsearch, const Pose& pose, bool isStartTree);
    bool canConnectTrees(std::shared_ptr<TreeNode<Keyframe>> startTreeNode, std::shared_ptr<TreeNode<Keyframe>> goalTreeNode);
    std::shared_ptr<AbstractNearestNeighbourSearch> nnSearch;
    std::shared_ptr<IPoseSampler> poseSampler;
    std::shared_ptr<IDynamicCollisionHandler> collisionHandler;
    std::shared_ptr<ITreeConnectPathGenerator> pathGenerator;
    std::unique_ptr<AbstractNearestNeighbourSearch> goalNNsearch;
    std::unique_ptr<Tree<Keyframe>> goalTree;
};



#endif //TARRTCONNECTSOLVER_H
