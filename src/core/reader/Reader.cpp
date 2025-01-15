//
// Created by arseniy on 13.1.25.
//

#include "Reader.h"

#include <fileParsers/animationParsers/FbxParser.h>



ReaderContext Reader::run()
{
    EnvSettings envSettings = inputParser->getEnvSettings();
    std::shared_ptr<RAPID_model> agent = std::move(meshParser->parse(envSettings.agentFilepath)[0]);
    std::vector<std::shared_ptr<RAPID_model>> obstacles = meshParser->parse(envSettings.obstaclesFilepath);
    std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    for (const std::string& filepath : envSettings.dynamicObjectsFilepaths)
    {
        dynamicObjects.push_back(animationParser->parse(filepath));
    }

    return ReaderContext{
        std::move(envSettings),
        std::move(agent),
        obstacles,
        dynamicObjects,
        componentsParser->getComponents(),
        componentsParser->getSharedVariables()
    };
}
