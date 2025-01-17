//
// Created by arseniy on 11.1.25.
//

#include "RapidCollisionHandlerFactory.h"

#include <fileParsers/meshParsers/RapidObjMeshParser.h>

#include "RapidCollisionHandler.h"

std::shared_ptr<ICollisionHandler> RapidCollisionHandlerFactory::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_shared<RapidCollisionHandler>(context.agent, context.obstacles);
}

