//
// Created by arseniy on 13.1.25.
//

#ifndef READER_H
#define READER_H
#include <memory>
#include <fileParsers/animationParsers/AnimationParser.h>
#include <fileParsers/meshParsers/MeshParser.h>
#include <input/InputParser.h>

#include "IReader.h"
#include "input/ComponentsParser.h"



class Reader : public IReader
{
public:
    ReaderContext run() override;
    Reader(std::unique_ptr<InputParser> inputParser,
            std::unique_ptr<MeshParser<RAPID_model>> meshParser,
            std::unique_ptr<AnimationParser<RAPID_model>> animationParser,
            std::unique_ptr<ComponentsParser> componentsParser) :
        inputParser(std::move(inputParser)), meshParser(std::move(meshParser)),
        animationParser(std::move(animationParser)), componentsParser(std::move(componentsParser)) {}

private:
    std::unique_ptr<InputParser> inputParser;
    std::unique_ptr<MeshParser<RAPID_model>> meshParser;
    std::unique_ptr<AnimationParser<RAPID_model>> animationParser;
    std::unique_ptr<ComponentsParser> componentsParser;
};



#endif //READER_H
