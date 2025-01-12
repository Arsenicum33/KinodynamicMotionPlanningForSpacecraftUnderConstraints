//
// Created by arseniy on 11.1.25.
//

#include "RapidCollisionHandlerFactory.h"

#include <fileParsers/meshParsers/RapidObjMeshParser.h>

#include "RapidCollisionHandler.h"

ICollisionHandler* RapidCollisionHandlerFactory::createComponent(
    std::unordered_map<std::string, std::any> data)
{
    try
    {
        auto agentFilepath = std::any_cast<std::string>(data.at("agentFilepath"));
        auto obstacleFilepath = std::any_cast<std::string>(data.at("obstacleFilepath"));
        auto& parser = *std::any_cast<RapidObjMeshParser*>(data.at("parser"));

        return new RapidCollisionHandler(agentFilepath, obstacleFilepath, parser);
    }
    catch (const std::out_of_range& e) {
        throw std::runtime_error("Missing required key in data map: " + std::string(e.what()));
    }
    catch (const std::bad_any_cast& e) {
        throw std::runtime_error("Type mismatch in data map: " + std::string(e.what()));
    }
}
