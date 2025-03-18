//
// Created by arseniy on 13.1.25.
//

#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <dto/EnvSettings.h>

#include "IExecutor.h"
#include "components/capabilities/Capability.h"
#include "components/solvers/newHierarchy/ISolver.h"
#include "core/creator/IComponentManager.h"


class Executor : public IExecutor
{
public:
    ExecutorOutput run(IComponentManager* component_manager, EnvSettings envSettings) override;
private:
    ExecutorOutput runAppropriateSolver(std::shared_ptr<ISolver> solver, const CapabilitySet& requiredCapabilities,
        const EnvSettings& envSettings) const;
    ExecutorOutput runMovingTargetSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const;
    ExecutorOutput runDynamicSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const;
    ExecutorOutput runStaticSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const;
};



#endif //EXECUTOR_H
