//
// Created by arseniy on 13.1.25.
//

#ifndef IREADER_H
#define IREADER_H
#include <string>

#include "input/componentsParser/ComponentsParser.h"
#include "dto/envSettings/EnvSettings.h"

struct ReaderContext {
    std::shared_ptr<EnvSettings> envSettings;
    std::vector<ComponentConfig> componentConfigs;
    const std::unordered_map<std::string, std::any> sharedVariables;

    ReaderContext(std::unique_ptr<EnvSettings> envSettings,
                  const std::vector<ComponentConfig>& componentConfigs,
                  const std::unordered_map<std::string, std::any>& sharedVariables)
    : envSettings(std::move(envSettings)),
      componentConfigs(componentConfigs),
      sharedVariables(sharedVariables) {}

};

class IReader
{
public:
    virtual ~IReader() = default;
    virtual ReaderContext run() = 0;
};
#endif //IREADER_H
