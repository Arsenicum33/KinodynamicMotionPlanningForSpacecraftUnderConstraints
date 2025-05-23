// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef COMPONENTSPARSER_H
#define COMPONENTSPARSER_H
#include <any>
#include <string>
#include <unordered_map>
#include <vector>
#include <jsoncpp/json/value.h>


struct ComponentConfig {
    std::string name;
    std::string type;
    std::unordered_map<std::string, std::any> config;
    std::string tag = "";
    std::vector<std::string> dependencies;
};

class ComponentsParser
{
public:
    ComponentsParser(const std::string& filepath) {parseFile(filepath);};
    const std::vector<ComponentConfig>& getComponents() const {return components;}
    const std::unordered_map<std::string, std::any>& getSharedVariables() const {return sharedVariables;}
private:
    std::vector<ComponentConfig> components;
    std::unordered_map<std::string, std::any> sharedVariables;

    void parseFile(const std::string& filepath);
    void parseShared(const Json::Value& value);
    void parseComponents(const Json::Value& value);

    std::vector<std::any> jsonToVector(const Json::Value& value);
};



#endif //COMPONENTSPARSER_H
