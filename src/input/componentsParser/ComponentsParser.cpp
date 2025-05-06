//
// Created by arseniy on 12.1.25.
//

#include "ComponentsParser.h"

#include <fstream>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <spdlog/spdlog.h>

void ComponentsParser::parseFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open config file: " + filepath);
    }

    Json::CharReaderBuilder reader;
    Json::Value jsonConfig;
    std::string errors;

    if (!parseFromStream(reader, file, &jsonConfig, &errors))
    {
        throw std::runtime_error("Failed to parse JSON: " + errors);
    }
    const Json::Value& sharedConfig = jsonConfig["shared"];

    parseShared(sharedConfig);

    const Json::Value& componentsArray = jsonConfig["components"];

    if (!componentsArray.isArray())
    {
        throw std::runtime_error("Invalid format: 'components' must be an array.");
    }

    parseComponents(componentsArray);


}

void ComponentsParser::parseShared(const Json::Value &sharedConfig)
{
    for (auto& key: sharedConfig.getMemberNames())
    {
        auto& value = sharedConfig[key];
        if (value.isString()) {
            sharedVariables[key] = value.asString();
        } else if (value.isDouble() || value.isInt()) {
            sharedVariables[key] = value.asDouble();
        } else if (value.isBool()) {
            sharedVariables[key] = value.asBool();
        } else {
            throw std::runtime_error("Unsupported config value type for key: " + key);
        }
    }
}

void ComponentsParser::parseComponents(const Json::Value &componentsArray)
{
    for (const auto& component : componentsArray)
    {
        if (!component.isMember("name") || !component.isMember("type") || !component.isMember("config"))
        {
            throw std::runtime_error("Invalid component definition: missing required fields.");
        }

        ComponentConfig config;
        config.name = component["name"].asString();
        config.type = component["type"].asString();
        if (component.isMember("tag"))
            config.tag = component["tag"].asString();
        const Json::Value& configValues = component["config"];

        for (const auto& key : configValues.getMemberNames())
        {
            const auto& value = configValues[key];
            if (value.isString()) {
                config.config[key] = value.asString();
            } else if (value.isDouble() || value.isInt()) {
                config.config[key] = value.asDouble();
            } else if (value.isBool()) {
                config.config[key] = value.asBool();
            } else if (value.isArray()) {
                config.config[key] = jsonToVector(value);
            } else {
                throw std::runtime_error("Unsupported config value type for key: " + key);
            }
        }

        if (component.isMember("dependencies"))
        {
            const Json::Value& dependencies = component["dependencies"];
            if (!dependencies.isArray())
            {
                throw std::runtime_error("Dependencies must be an array.");
            }
            for (const auto& dependency : dependencies)
            {
                std::string dependencyName = dependency.asString();
                config.dependencies.push_back(dependencyName);
            }
        }


        components.push_back(std::move(config));

    }
}

std::vector<std::any> ComponentsParser::jsonToVector(const Json::Value &array)
{
    if (!array.isArray())
    {
        spdlog::error("Cant convert value to vector, not an array");
        throw std::runtime_error("Cant convert value to vector, not an array");
    }
    std::vector<std::any> result;
    for (const auto& value : array)
    {
        result.push_back(value);
    }
    return result;
}
