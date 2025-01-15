//
// Created by arseniy on 15.1.25.
//

#include "RapidDynamicCollisionHandlerFactory.h"

#include "RapidDynamicCollisionHandler.h"

std::shared_ptr<ICollisionHandler> RapidDynamicCollisionHandlerFactory::createComponent(ComponentConfig &config,
                                                                                        ReaderContext &context)
{
    return std::make_shared<RapidDynamicCollisionHandler>(context.agent, std::move(context.obstacles), std::move(context.dynamicObjects));
}
