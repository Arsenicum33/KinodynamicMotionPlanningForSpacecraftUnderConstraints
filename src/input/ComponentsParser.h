//
// Created by arseniy on 12.1.25.
//

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
};



#endif //COMPONENTSPARSER_H
