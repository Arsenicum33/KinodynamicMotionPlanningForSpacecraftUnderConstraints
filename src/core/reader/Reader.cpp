//
// Created by arseniy on 13.1.25.
//

#include "Reader.h"

#include <fileParsers/animationParsers/FbxParser.h>

void Reader::initialize(int argc, char* argv[])
{
    inputParser = std::make_unique<InputParser>(argc, argv, argc!=2);
    meshParser = std::make_unique<RapidObjMeshParser>();
    animationParser = std::make_unique<FbxParser<RAPID_model>>(meshParser.get());
    componentsParser = std::make_unique<ComponentsParser>(COMPONENTS_CONFIG_FILEPATH);
}

ReaderContext Reader::run(int argc, char* argv[])
{
    initialize(argc, argv);
    EnvSettings envSettings = inputParser->getEnvSettings();
    std::unique_ptr<RAPID_model> agent = std::move(meshParser->parse(envSettings.agentFilepath)[0]);
    std::vector<std::unique_ptr<RAPID_model>> obstacles = meshParser->parse(envSettings.obstaclesFilepath);
    std::vector<std::unique_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    for (const std::string& filepath : envSettings.dynamicObjectsFilepaths)
    {
        dynamicObjects.push_back(animationParser->parse(filepath));
    }

    return ReaderContext{
        std::move(envSettings),
        std::move(agent),
        std::move(obstacles),
        std::move(dynamicObjects),
        componentsParser->getComponents(),
        componentsParser->getSharedVariables()
    };
}
