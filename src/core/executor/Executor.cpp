//
// Created by arseniy on 13.1.25.
//

#include "Executor.h"
#include <spdlog/spdlog.h>

#include "components/capabilities/CapabilityManager.h"
#include "components/solvers/solvers/dynamic/IDynamicSolver.h"
#include "components/solvers/solvers/dynamic/movingTarget/IMovingTargetSolver.h"
#include "components/solvers/solvers/static/IStaticSolver.h"
#include "dto/EnvSettings.h"

ExecutorOutput Executor::run(IComponentManager* componentManager, EnvSettings envSettings)
{
    std::shared_ptr<CapabilityManager> capabilityManager = CapabilityManager::getInstance();
    CapabilitySet capabilities = capabilityManager->getRequiredCapabilities();
    std::shared_ptr<IComponent> solver = componentManager->getComponent("Solver");
    try
    {
        return runAppropriateSolver(solver, capabilities, envSettings);
    }
    catch (std::exception& e)
    {
        spdlog::error(e.what());
        throw e;
    }
}

ExecutorOutput Executor::runAppropriateSolver(std::shared_ptr<IComponent> solver,
    const CapabilitySet &requiredCapabilities, const EnvSettings &envSettings) const
{
    if (requiredCapabilities.contains(Capability::MovingTarget))
    {
        spdlog::info("Solving for Moving Target scenario");
        return runMovingTargetSolver(solver, envSettings);
    }
    if (requiredCapabilities.contains(Capability::DynamicEnv))
    {
        spdlog::info("Solving for Dynamic env scenario");
        return runDynamicSolver(solver, envSettings);
    }
    if (requiredCapabilities.contains(Capability::StaticEnv))
    {
        spdlog::info("Solving for Static env scenario");
        return runStaticSolver(solver, envSettings);
    }
    spdlog::error("Executor failed to get a suitable solver");
    throw std::runtime_error("Executor failed to get a suitable solver");
}

ExecutorOutput Executor::runMovingTargetSolver(std::shared_ptr<IComponent> solver, const EnvSettings &envSettings) const
{
    std::shared_ptr<IMovingTargetSolver> castedSolver = std::dynamic_pointer_cast<IMovingTargetSolver>(solver);
    std::shared_ptr<DynamicObject<RAPID_model>> target = std::get<std::shared_ptr<DynamicObject<RAPID_model> > >(
        envSettings.target);
    const Animation *targetAnimation = target->getAnimation();
    std::vector<Keyframe> keyframes = castedSolver->solve(envSettings.startPose, *targetAnimation);
    return ExecutorOutput{ keyframes };
}

ExecutorOutput Executor::runDynamicSolver(std::shared_ptr<IComponent> solver, const EnvSettings &envSettings) const
{
    std::shared_ptr<IDynamicSolver> castedSolver = std::dynamic_pointer_cast<IDynamicSolver>(solver);
    Pose target = std::get<Pose>(envSettings.target);
    std::vector<Keyframe> keyframes = castedSolver->solve(envSettings.startPose, target);
    return ExecutorOutput{ keyframes };
}

ExecutorOutput Executor::runStaticSolver(std::shared_ptr<IComponent> solver, const EnvSettings &envSettings) const
{
    std::shared_ptr<IStaticSolver> castedSolver = std::dynamic_pointer_cast<IStaticSolver>(solver);
    Pose target = std::get<Pose>(envSettings.target);
    std::vector<Pose> keyframes = castedSolver->solve(envSettings.startPose, target);
    return ExecutorOutput{ keyframes };
}



