//
// Created by arseniy on 11.1.25.
//

#include "RapidCollisionHandlerFactory.h"

#include <fileParsers/meshParsers/RapidObjMeshParser.h>

#include "RapidCollisionHandler.h"

std::unique_ptr<ICollisionHandler> RapidCollisionHandlerFactory::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<RapidCollisionHandler>(context.agent, context.obstacles);
}

