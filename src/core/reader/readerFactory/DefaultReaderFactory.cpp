// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "DefaultReaderFactory.h"

#include <input/meshParsers/rapidObjMeshParser/RapidObjMeshParser.h>

#include "core/reader/Reader.h"
#include "input/animationParsers/fbxParser/FbxParser.h"


std::unique_ptr<IReader> DefaultReaderFactory::createReader(int argc, char* argv[])
{
    std::unique_ptr<InputParser> inputParser = std::make_unique<InputParser>(argc, argv, argc<2);
    std::unique_ptr<MeshParser<RAPID_model>> meshParser = std::make_unique<RapidObjMeshParser>();
    std::unique_ptr<AnimationParser<RAPID_model>> animationParser = std::make_unique<FbxParser<RAPID_model>>(meshParser.get());

    return std::make_unique<Reader>(std::move(inputParser), std::move(meshParser), std::move(animationParser));
}
