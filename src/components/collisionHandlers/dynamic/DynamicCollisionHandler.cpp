//
// Created by arseniy on 17.3.25.
//

#include "DynamicCollisionHandler.h"

#include "components/collisionHandlers/static/StaticCollisionHandler.h"

std::unique_ptr<IComponent> DynamicCollisionHandler::createComponent(const ComponentConfig &config,
                                                                     const ReaderContext &context)
{
    auto staticComponent = StaticCollisionHandler::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<IStaticCollisionHandler*>(staticComponent.get()))
    {
        staticComponent.release();
        std::unique_ptr<IStaticCollisionHandler> staticHandler(castPtr);
        return std::make_unique<DynamicCollisionHandler>(std::move(staticHandler), context.envSettings.dynamicObjects);
    }
    spdlog::error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
    throw std::runtime_error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
}

bool DynamicCollisionHandler::isCollisionFree(Keyframe &position) const
{
    return staticHandler->isCollisionFree(position) && isNotCollidingWithDynamicObjects(position);
}

bool DynamicCollisionHandler::isNotCollidingWithDynamicObjects(Keyframe &keyframe) const
{
    double time = keyframe.time;
    for (auto& dynamicObject : dynamicObjects)
    {
        Keyframe dynamicObjectKeyframe = interpolator->extractKeyframeAtTime(dynamicObject->getAnimation(), time);//KeyframeMath::getKeyframeAtTime(dynamicObject.get(), time);
        RAPID_Collide(keyframe.rotation, keyframe.translation.data(), staticHandler->getAgent().get(),
                        dynamicObjectKeyframe.rotation, dynamicObjectKeyframe.translation.data(), dynamicObject->getMesh());
        if (RAPID_num_contacts > 0)
            return false;
    }
    return true;
}

void DynamicCollisionHandler::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IDynamicCollisionHandler::resolveDependencies(config, manager);
    interpolator = std::dynamic_pointer_cast<IDynamicInterpolator>(manager->getComponent(ComponentType::Interpolator));
}
