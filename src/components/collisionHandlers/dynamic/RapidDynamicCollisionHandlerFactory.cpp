//
// Created by arseniy on 15.1.25.
//

#include "RapidDynamicCollisionHandlerFactory.h"

#include "RapidDynamicCollisionHandler.h"

std::unique_ptr<ICollisionHandler> RapidDynamicCollisionHandlerFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<RapidDynamicCollisionHandler>(context.agent, context.obstacles, context.dynamicObjects);
}
