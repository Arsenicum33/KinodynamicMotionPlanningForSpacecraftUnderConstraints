//
// Created by arseniy on 12.1.25.
//

#ifndef COMPONENTSPARSER_H
#define COMPONENTSPARSER_H
#include <any>
#include <string>
#include <unordered_map>
#include <vector>


struct ComponentConfig {
    std::string name;
    std::string type;
    std::unordered_map<std::string, std::any> config;
};

class ComponentsParser
{
public:
    ComponentsParser(const std::string& filepath) {parseFile(filepath);};
    const std::vector<ComponentConfig>& getComponents() const {return components;}
private:
    std::vector<ComponentConfig> components;
    void parseFile(const std::string& filepath);
};



#endif //COMPONENTSPARSER_H
