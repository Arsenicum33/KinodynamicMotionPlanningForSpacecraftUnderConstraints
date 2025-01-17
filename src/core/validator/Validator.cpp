//
// Created by arseniy on 13.1.25.
//

#include "Validator.h"

#include <poses/static/PoseMath.h>

#include "components/collisionHandlers/dynamic/IDynamicCollisionHandler.h"
#include "components/collisionHandlers/dynamic/RapidDynamicCollisionHandler.h"
#include "poses/dynamic/KeyframeMath.h"

void Validator::validate(IComponentManager* component_manager, EnvSettings envSettings, ExecutorOutput executorOutput)
{
    std::vector<Keyframe> path = std::get<std::vector<Keyframe>>(executorOutput.path);
    auto collisionHandler = std::dynamic_pointer_cast<IDynamicCollisionHandler>(component_manager->getComponent("CollisionHandler"));
    bool isPathCollisionFree = collisionHandler->areKeyframesCollisionFree(path);
    if (!isPathCollisionFree)
        throw std::runtime_error("Collision detected! Path is incorrect.");
}

void Validator::test_dynamic_collisions(IComponentManager *component_manager, EnvSettings envSettings)
{
    auto collisionHandler = std::dynamic_pointer_cast<RapidDynamicCollisionHandler>(component_manager->getComponent("CollisionHandler"));

    std::array<double, 3> trans = {-8.7,20.4,-8.4};
    //std::array<double, 3> rot = {13.75,49.11,-90.2};
    //Keyframe testedKeyframe(trans, PoseMath::eulerToRotationMatrix(rot), 31);
    Keyframe testedKeyframe(trans, 30);
    bool isCollisionFree = collisionHandler->isKeyframeCollisionFree(testedKeyframe);
    printf(isCollisionFree ? "Collision NOT detected!\n" : "Collision detected!\n");
}
