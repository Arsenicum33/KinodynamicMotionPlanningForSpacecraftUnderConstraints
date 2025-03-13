//
// Created by arseniy on 13.1.25.
//

#include "Exporter.h"

#include <components/collisionHandlers/ICollisionHandler.h>
#include <components/exporters/AbstractExporter.h>

#include "components/collisionHandlers/dynamic/rapid/RapidDynamicCollisionHandler.h"

void Exporter::exportOutput(IComponentManager* componentManager,ExecutorOutput executorOutput)
{
    std::shared_ptr<AbstractExporter<Keyframe>> dynamicExporter =
     std::dynamic_pointer_cast<AbstractExporter<Keyframe>>(componentManager->getComponent(ComponentType::Exporter));

    if (dynamicExporter)
    {
        std::vector<Keyframe> data = std::get<std::vector<Keyframe>>(executorOutput.path);
        auto result = dynamicExporter->exportPoses(data);
        auto collisionHandler = std::dynamic_pointer_cast<RapidDynamicCollisionHandler>(componentManager->getComponent(ComponentType::CollisionHandler));
       // printf(collisionHandler->areKeyframesCollisionFree(result, TODO)? "Result collision-free" : "Collision detected, path invalid");
        return;
    }

    // Try static solver if dynamic solver is not available
    std::shared_ptr<AbstractExporter<Pose>> staticExporter =
        std::dynamic_pointer_cast<AbstractExporter<Pose>>(componentManager->getComponent(ComponentType::Exporter));

    if (staticExporter)
    {
        std::vector<Pose> data = std::get<std::vector<Pose>>(executorOutput.path);
        staticExporter->exportPoses(data);
        return;
    }

    throw std::runtime_error("No suitable solver found in component manager.");
}
