//
// Created by arseniy on 12.1.25.
//

#include "ComponentsParser.h"

#include <fstream>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>

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

    const Json::Value& componentsArray = jsonConfig["components"];

    if (!componentsArray.isArray())
    {
        throw std::runtime_error("Invalid format: 'components' must be an array.");
    }

    for (const auto& component : componentsArray)
    {
        if (!component.isMember("name") || !component.isMember("type") || !component.isMember("config"))
        {
            throw std::runtime_error("Invalid component definition: missing required fields.");
        }

        ComponentConfig config;
        config.name = component["name"].asString();
        config.type = component["type"].asString();
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
            } else {
                throw std::runtime_error("Unsupported config value type for key: " + key);
            }
        }

        components.push_back(std::move(config));

    }
}
