//
// Created by arseniy on 22.10.24.
//

#ifndef PLANNINGABSTRACTTREESOLVER_H
#define PLANNINGABSTRACTTREESOLVER_H

#include "Tree.h"
#include "TreeNode.h"
#include "../IStaticSolverTemplated.h"
#include "../../pathGenerator/IPathGenerator.h"
#include "components/solvers/IStaticSolver.h"

template <typename ConfigType>
class AbstractTreeSolver : public IStaticSolverTemplated<ConfigType>
{
protected:
    std::unique_ptr<Tree<Pose>> tree;
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::shared_ptr<IPathGenerator<Pose>> pathGenerator;

    AbstractTreeSolver(const ConfigType& config,  const EnvSettings& envSettings)
        : IStaticSolverTemplated<ConfigType>(config, envSettings)
    {
    }

public:
    void build() override {tree = std::make_unique<Tree<Pose>>(distanceMetric);}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override
    {
        IStaticSolverTemplated<ConfigType>::resolveDependencies(config, manager);
        this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent("DistanceMetric"));
        this->pathGenerator = std::dynamic_pointer_cast<IPathGenerator<Pose>>(manager->getComponent("PathGenerator"));
    }
};



#endif //PLANNINGABSTRACTTREESOLVER_H
