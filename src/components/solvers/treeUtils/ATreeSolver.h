//
// Created by arseniy on 22.10.24.
//

#ifndef PLANNINGABSTRACTTREESOLVER_H
#define PLANNINGABSTRACTTREESOLVER_H

#include <spdlog/spdlog.h>

#include "Tree.h"
#include "TreeNode.h"
#include "../../pathGenerator/IPathGenerator.h"
#include "components/solvers/ASolver.h"

template <typename StoredPositionType, typename DistanceMetricPositionType>
class ATreeSolver : public ASolver
{
protected:
    std::unique_ptr<Tree<StoredPositionType>> tree;
    std::shared_ptr<IDistanceMetric> distanceMetric;
public:
    void build() override {tree = std::make_unique<Tree<StoredPositionType>>(distanceMetric);}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override
    {
        ASolver::resolveDependencies(config, manager);
        this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
    }
};



#endif //PLANNINGABSTRACTTREESOLVER_H
