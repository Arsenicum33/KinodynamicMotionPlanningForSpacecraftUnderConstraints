//
// Created by arseniy on 13.1.25.
//

#include "Executor.h"

#include <components/solvers/IStaticSolver.h>

#include "components/solvers/dynamic/IDynamicSolver.h"

ExecutorOutput Executor::run(IComponentManager* componentManager, EnvSettings envSettings)
{
    std::shared_ptr<IDynamicSolver> dynamicSolver =
        std::dynamic_pointer_cast<IDynamicSolver>(componentManager->getComponent("Solver"));

    if (dynamicSolver) {
        std::vector<Keyframe> solution = dynamicSolver->solve(envSettings.startPose, envSettings.endPose);
        return ExecutorOutput{ solution };
    }

    // Try static solver if dynamic solver is not available
    std::shared_ptr<IStaticSolver> staticSolver =
        std::dynamic_pointer_cast<IStaticSolver>(componentManager->getComponent("Solver"));

    if (staticSolver) {
        std::vector<Pose> solution = staticSolver->solve(envSettings.startPose, envSettings.endPose);
        return ExecutorOutput{ solution };
    }

    throw std::runtime_error("No suitable solver found in component manager.");
}
