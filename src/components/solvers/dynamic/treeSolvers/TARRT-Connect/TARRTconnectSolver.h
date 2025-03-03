//
// Created by arseniy on 19.1.25.
//

#ifndef TARRTCONNECTSOLVER_H
#define TARRTCONNECTSOLVER_H
#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>

#include "components/collisionHandlers/dynamic/IDynamicCollisionHandler.h"
#include "components/pathGenerator/ITreeConnectPathGenerator.h"
#include "components/solvers/dynamic/configs/treeSolvers/TARRT-Connect/TARRTconnectSolverConfig.h"
#include "components/solvers/dynamic/treeSolvers/IDynamicTreeSolver.h"
#include "components/sampling/IPoseSampler.h"


class TARRTconnectSolver : public IDynamicTreeSolver<TARRTconnectSolverConfig>
{
public:
    std::vector<Keyframe> solve(const Pose& startPosition, const Pose& goalPosition) override;
    TARRTconnectSolver(const TARRTconnectSolverConfig& config,  const EnvSettings& envSettings) :
        IDynamicTreeSolver(config, envSettings) {}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    void build() override;

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
