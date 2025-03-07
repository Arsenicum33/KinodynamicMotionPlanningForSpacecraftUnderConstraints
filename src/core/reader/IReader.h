//
// Created by arseniy on 13.1.25.
//

#ifndef IREADER_H
#define IREADER_H
#include <string>
#include <dto/EnvSettings.h>
#include "input/ComponentsParser.h"

#define COMPONENTS_CONFIG_FILEPATH "../components.json"

struct ReaderContext {
    const EnvSettings envSettings;
    std::vector<ComponentConfig> componentConfigs;
    const std::unordered_map<std::string, std::any> sharedVariables;

    ReaderContext(const EnvSettings& envSettings,
                  const std::vector<ComponentConfig>& componentConfigs,
                  const std::unordered_map<std::string, std::any>& sharedVariables)
    : envSettings(envSettings),
      componentConfigs(componentConfigs),
      sharedVariables(sharedVariables) {}

    ReaderContext(const ReaderContext&) = default;
};

class IReader
{
public:
    virtual ~IReader() = default;
    virtual ReaderContext run() = 0;
};
#endif //IREADER_H
