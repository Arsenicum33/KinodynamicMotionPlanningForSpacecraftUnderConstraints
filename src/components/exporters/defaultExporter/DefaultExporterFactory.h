//
// Created by arseniy on 14.1.25.
//

#ifndef DEFAULTEXPORTERFACTORY_H
#define DEFAULTEXPORTERFACTORY_H
#include <components/exporters/AbstractExporter.h>

#include "components/IComponentFactory.h"


class DefaultExporterFactory : public IComponentFactory<AbstractExporter<Pose>>
{
public:
    std::unique_ptr<AbstractExporter<Pose>> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //DEFAULTEXPORTERFACTORY_H
