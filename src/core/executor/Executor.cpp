//
// Created by arseniy on 13.1.25.
//

#include "Executor.h"
#include <spdlog/spdlog.h>

#include "components/capabilities/manager/CapabilityManager.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"

ExecutorOutput Executor::run(IComponentManager* componentManager, EnvSettings envSettings)
{
    std::shared_ptr<CapabilityManager> capabilityManager = CapabilityManager::getInstance();
    CapabilitySet capabilities = capabilityManager->getRequiredCapabilities();
    std::shared_ptr<IComponent> solverComponent = componentManager->getComponent(ComponentType::Solver);
    try
    {
        std::shared_ptr<ISolver> solver = std::dynamic_pointer_cast<ISolver>(solverComponent);
        return runAppropriateSolver(solver, capabilities, envSettings);
    }
    catch (std::exception& e)
    {
        spdlog::error(e.what());
        throw e;
    }
}

ExecutorOutput Executor::runAppropriateSolver(std::shared_ptr<ISolver> solver,
    const CapabilitySet &requiredCapabilities, const EnvSettings &envSettings) const
{
    if (requiredCapabilities.contains(Capability::KinodynamicEnv))
    {
        spdlog::info("Solving for Kinodynamic scenario");
        return runKinodynamicSolver(solver, envSettings);
    }
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

ExecutorOutput Executor::runMovingTargetSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const
{
    std::shared_ptr<DynamicObject<RAPID_model>> target = std::get<std::shared_ptr<DynamicObject<RAPID_model> > >(
        envSettings.target);
    const Animation *targetAnimation = target->getAnimation();
    Keyframe start(envSettings.startPose, 1.0);
    std::vector<std::any> result = solver->solve(start, *targetAnimation);
    return ExecutorOutput{ result };
}

ExecutorOutput Executor::runDynamicSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const
{
    Pose target = std::get<Pose>(envSettings.target);
    Keyframe start(envSettings.startPose, 1.0);
    std::vector<std::any> result = solver->solve(start, target);
    return ExecutorOutput{ result };
}

ExecutorOutput Executor::runStaticSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const
{
    Pose target = std::get<Pose>(envSettings.target);
    std::vector<std::any> result = solver->solve(envSettings.startPose, target);
    return ExecutorOutput{ result };
}

ExecutorOutput Executor::runKinodynamicSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const
{
    std::shared_ptr<DynamicObject<RAPID_model>> target = std::get<std::shared_ptr<DynamicObject<RAPID_model> > >(
    envSettings.target);
    const Animation *targetAnimation = target->getAnimation();
    Keyframe startKeyframe(envSettings.startPose, 1.0);
    State start(startKeyframe, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0});
    std::vector<std::any> result = solver->solve(start, *targetAnimation);
    return ExecutorOutput{ result };
}



