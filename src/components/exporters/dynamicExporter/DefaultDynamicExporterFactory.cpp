//
// Created by arseniy on 17.1.25.
//

#include "DefaultDynamicExporterFactory.h"

#include "DefaultDynamicExporter.h"

std::unique_ptr<AbstractExporter<Keyframe>> DefaultDynamicExporterFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    std::string filename = std::any_cast<std::string>(configMap.at("filename"));
    int fps = static_cast<int>(std::any_cast<double>(configMap.at("fps")));
    return std::make_unique<DefaultDynamicExporter>(filename,fps);
}
