//
// Created by arseniy on 14.1.25.
//

#include "DefaultExporterFactory.h"

#include "DefaultExporter.h"

std::shared_ptr<AbstractExporter<Pose>> DefaultExporterFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    std::string filename = std::any_cast<std::string>(configMap.at("filename"));

    return std::make_shared<DefaultExporter>(filename);
}
