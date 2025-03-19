//
// Created by arseniy on 13.1.25.
//

#ifndef READER_H
#define READER_H
#include <memory>
#include <input/meshParsers/MeshParser.h>

#include "IReader.h"
#include "input/animationParsers/AnimationParser.h"
#include "input/inputParser/InputParser.h"


class Reader : public IReader
{
public:
    ReaderContext run() override;
    Reader(std::unique_ptr<InputParser> inputParser,
            std::unique_ptr<MeshParser<RAPID_model>> meshParser,
            std::unique_ptr<AnimationParser<RAPID_model>> animationParser) :
        inputParser(std::move(inputParser)), meshParser(std::move(meshParser)),
        animationParser(std::move(animationParser)) {}

private:
    EnvSettings processRawEnvSettings(const EnvSettingsRaw& rawSettings);
    std::unique_ptr<InputParser> inputParser;
    std::unique_ptr<MeshParser<RAPID_model>> meshParser;
    std::unique_ptr<AnimationParser<RAPID_model>> animationParser;
    std::unique_ptr<ComponentsParser> componentsParser;
};



#endif //READER_H
