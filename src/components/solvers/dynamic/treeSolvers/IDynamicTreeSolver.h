//
// Created by arseniy on 14.1.25.
//

#ifndef IDYNAMICTREESOLVER_H
#define IDYNAMICTREESOLVER_H
#include <components/distanceMeasurement/IDistanceMetric.h>
#include <components/pathGenerator/IPathGenerator.h>
#include <components/solvers/treeSolvers/Tree.h>

#include "components/solvers/dynamic/IDynamicSolver.h"
#include "components/solvers/dynamic/IDynamicSolverTemplated.h"
#include "components/solvers/dynamic/configs/treeSolvers/IDynamicTreeSolverConfig.h"

template <typename ConfigType>
class IDynamicTreeSolver : public IDynamicSolverTemplated<ConfigType>
{
public:
    void build() override {tree = std::make_unique<Tree<Keyframe>>(distanceMetric);}
    void resolveDependencies(ComponentConfig &config, ComponentManager *manager) override
    {
        IDynamicSolverTemplated<ConfigType>::resolveDependencies(config, manager);
        this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent("DistanceMetric"));
        this->pathGenerator = std::dynamic_pointer_cast<IPathGenerator<Keyframe>>(manager->getComponent("PathGenerator"));
    }
protected:
    IDynamicTreeSolver(const ConfigType& config,  const EnvSettings& envSettings)
        : IDynamicSolverTemplated<ConfigType>(config, envSettings) {}




    std::unique_ptr<Tree<Keyframe>> tree;
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::shared_ptr<IPathGenerator<Keyframe>> pathGenerator;

};



#endif //IDYNAMICTREESOLVER_H
