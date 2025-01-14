//
// Created by arseniy on 13.1.25.
//

#ifndef IREADER_H
#define IREADER_H
#include <EnvSettings.h>
#include <RAPID.H>
#include <string>
#include <poses/dynamic/DynamicObject.h>

#include "input/ComponentsParser.h"

#define COMPONENTS_CONFIG_FILEPATH "../components.json"

struct ReaderContext {
    const EnvSettings envSettings;
    std::shared_ptr<RAPID_model> agent;
    std::vector<std::shared_ptr<RAPID_model>> obstacles;
    const std::vector<std::unique_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    std::vector<ComponentConfig> componentConfigs;
    const std::unordered_map<std::string, std::any> sharedVariables;
};

class IReader
{
public:
    virtual ~IReader() = default;
    virtual ReaderContext run() = 0;
};
#endif //IREADER_H
