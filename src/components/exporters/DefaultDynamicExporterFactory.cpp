//
// Created by arseniy on 17.1.25.
//

#include "DefaultDynamicExporterFactory.h"

#include "DefaultDynamicExporter.h"

std::shared_ptr<AbstractExporter<Keyframe>> DefaultDynamicExporterFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    std::string filename = std::any_cast<std::string>(configMap.at("filename"));

    return std::make_shared<DefaultDynamicExporter>(filename);
}
