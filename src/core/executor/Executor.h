//
// Created by arseniy on 13.1.25.
//

#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <dto/EnvSettings.h>

#include "IExecutor.h"
#include "components/capabilities/Capability.h"
#include "core/creator/IComponentManager.h"


class Executor : public IExecutor
{
public:
    ExecutorOutput run(IComponentManager* component_manager, EnvSettings envSettings) override;
private:
    ExecutorOutput runAppropriateSolver(std::shared_ptr<IComponent> solver, const CapabilitySet& requiredCapabilities,
        const EnvSettings& envSettings) const;
    ExecutorOutput runMovingTargetSolver(std::shared_ptr<IComponent> solver, const EnvSettings &envSettings) const;
    ExecutorOutput runDynamicSolver(std::shared_ptr<IComponent> solver, const EnvSettings &envSettings) const;
    ExecutorOutput runStaticSolver(std::shared_ptr<IComponent> solver, const EnvSettings &envSettings) const;
};



#endif //EXECUTOR_H
