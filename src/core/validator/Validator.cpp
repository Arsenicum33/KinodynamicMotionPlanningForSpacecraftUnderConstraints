//
// Created by arseniy on 13.1.25.
//

#include "Validator.h"

#include <poses/static/PoseMath.h>
#include <spdlog/spdlog.h>

#include "components/capabilities/CapabilityManager.h"
#include "components/collisionHandlers/dynamic/IDynamicCollisionHandler.h"
#include "components/collisionHandlers/dynamic/RapidDynamicCollisionHandler.h"
#include "poses/dynamic/KeyframeMath.h"

void Validator::validate(IComponentManager* componentManager, const EnvSettings& envSettings, const ExecutorOutput& executorOutput)
{
    if (std::holds_alternative<std::vector<Pose>>(executorOutput.path))
    {
        validateStatic(componentManager, envSettings, executorOutput);
    }
    else
    {
        validateDynamic(componentManager, envSettings, executorOutput);
    }
}

void Validator::validateComponents(IComponentManager *componentManager, const ReaderContext& readerContext)
{
    std::shared_ptr<CapabilityManager> capabilityManager = CapabilityManager::getInstance();
    CapabilitySet requiredCapabilities = capabilityManager->getRequiredCapabilities();
    const std::vector<std::shared_ptr<const IComponent>> components = componentManager->getComponents();
    for (auto& component : components)
    {
        CapabilitySet componentCapabilities = component->getCapabilities();
        for (auto& requiredCapability : requiredCapabilities)
        {
            if (!componentCapabilities.contains(requiredCapability))
            {
                spdlog::error("Component {} does not support {}", component->getName(), capabilityToString(requiredCapability));
                throw new std::runtime_error(component->getName() + "does not support required capabilities");
            }
        }
    }

    spdlog::info("Component validation successful");
}

void Validator::validateStatic(IComponentManager *componentManager, const EnvSettings &envSettings,
    const ExecutorOutput &executorOutput)
{
    std::vector<Pose> path = std::get<std::vector<Pose>>(executorOutput.path);
    auto collisionHandler = std::dynamic_pointer_cast<ICollisionHandler>(componentManager->getComponent("CollisionHandler"));

    Pose* collidingPose = nullptr;
    bool isPathCollisionFree = collisionHandler->arePosesCollisionFree(path, collidingPose);
    if (!isPathCollisionFree)
    {
        spdlog::error("Computed path is not collision free. Colliding pose {}", collidingPose->toString());
        throw std::runtime_error("Computed path is not collision free");
    }
}

void Validator::validateDynamic(IComponentManager *componentManager, const EnvSettings &envSettings,
    const ExecutorOutput &executorOutput)
{
    std::vector<Keyframe> path = std::get<std::vector<Keyframe>>(executorOutput.path);
    auto collisionHandler = std::dynamic_pointer_cast<IDynamicCollisionHandler>(componentManager->getComponent("CollisionHandler"));

    Keyframe* collidingKeyframe = nullptr;
    bool isPathCollisionFree = collisionHandler->areKeyframesCollisionFree(path, collidingKeyframe);
    if (!isPathCollisionFree)
    {
        spdlog::error("Computed path is not collision free. Colliding pose {}", collidingKeyframe->toString());
        throw std::runtime_error("Computed path is not collision free");
    }
}


