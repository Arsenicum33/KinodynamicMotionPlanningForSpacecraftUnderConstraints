// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "IExecutor.h"
#include "components/capabilities/Capability.h"
#include "components/solvers/ISolver.h"
#include "core/creator/IComponentManager.h"
#include "dto/envSettings/EnvSettingsAstro.h"


class Executor : public IExecutor
{
public:
    ExecutorOutput run(IComponentManager* component_manager, const EnvSettings& envSettings) override;
private:
    std::vector<std::any> runAppropriateSolver(std::shared_ptr<ISolver> solver, const CapabilitySet& requiredCapabilities,
        const EnvSettings& envSettings, IComponentManager* componentManager) const;
    std::vector<std::any> runMovingTargetSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const;
    std::vector<std::any> runDynamicSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const;
    std::vector<std::any> runStaticSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const;
    std::vector<std::any> runKinodynamicSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const;
    std::vector<std::any> runAstrodynamicSolver(std::shared_ptr<ISolver> solver, const EnvSettingsAstro &envSettings,
        IComponentManager* componentManager) const;
};



#endif //EXECUTOR_H
