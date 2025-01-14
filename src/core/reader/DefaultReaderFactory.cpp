//
// Created by arseniy on 14.1.25.
//

#include "DefaultReaderFactory.h"


std::unique_ptr<IReader> DefaultReaderFactory::createReader(int argc, char* argv[])
{
    std::unique_ptr<InputParser> inputParser = std::make_unique<InputParser>(argc, argv, argc!=2);
    std::unique_ptr<MeshParser<RAPID_model>> meshParser = std::make_unique<RapidObjMeshParser>();
    std::unique_ptr<AnimationParser<RAPID_model>> animationParser = std::make_unique<FbxParser<RAPID_model>>(meshParser.get());
    std::unique_ptr<ComponentsParser> componentsParser = std::make_unique<ComponentsParser>(COMPONENTS_CONFIG_FILEPATH);

    return std::make_unique<Reader>(std::move(inputParser), std::move(meshParser), std::move(animationParser), std::move(componentsParser));
}
