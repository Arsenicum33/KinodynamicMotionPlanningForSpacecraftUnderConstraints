//
// Created by arseniy on 15.1.25.
//

#include "RapidDynamicCollisionHandlerFactory.h"

#include "RapidDynamicCollisionHandler.h"

std::shared_ptr<ICollisionHandler> RapidDynamicCollisionHandlerFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_shared<RapidDynamicCollisionHandler>(context.agent, context.obstacles, context.dynamicObjects);
}
