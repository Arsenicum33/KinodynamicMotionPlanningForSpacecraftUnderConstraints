//
// Created by arseniy on 13.1.25.
//

#ifndef READER_H
#define READER_H
#include <memory>
#include <input/meshParsers/MeshParser.h>

#include "IReader.h"
#include "dto/envSettings/EnvSettingsAstro.h"
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
    std::unique_ptr<EnvSettings> processEnvSettingsRaw(EnvSettingsRaw* rawSettings);
    std::unique_ptr<EnvSettingsAstro> processEnvSettingsAstroRaw(EnvSettingsAstroRaw* rawSettings);
    void createCelestialBodies(std::unordered_map<std::string, std::unordered_map<std::string, std::any>> celestialBodies);
    void scaleEnvSettings(EnvSettings& envSettings, double scale);
    std::variant<Pose, std::shared_ptr<DynamicObject<RAPID_model>>> processTarget(const EnvSettingsRaw& rawSettings);
    std::unique_ptr<InputParser> inputParser;
    std::unique_ptr<MeshParser<RAPID_model>> meshParser;
    std::unique_ptr<AnimationParser<RAPID_model>> animationParser;
    std::unique_ptr<ComponentsParser> componentsParser;
    std::vector<CelestialBody> celestialBodies;
};



#endif //READER_H
