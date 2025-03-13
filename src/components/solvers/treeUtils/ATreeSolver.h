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

template <typename ConfigType, typename StoredPositionType, typename DistanceMetricPositionType>
class ATreeSolver : public ASolver<ConfigType>
{
protected:
    std::unique_ptr<Tree<StoredPositionType, DistanceMetricPositionType>> tree;
    std::shared_ptr<IDistanceMetric> distanceMetric;


    ATreeSolver(const ConfigType& config,  const EnvSettings& envSettings)
        : ASolver<ConfigType>(config, envSettings.boundaries) {}

public:
    void build() override {tree = std::make_unique<Tree<StoredPositionType, DistanceMetricPositionType>>(distanceMetric);}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override
    {
        ASolver<ConfigType>::resolveDependencies(config, manager);
        this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
    }
};



#endif //PLANNINGABSTRACTTREESOLVER_H
