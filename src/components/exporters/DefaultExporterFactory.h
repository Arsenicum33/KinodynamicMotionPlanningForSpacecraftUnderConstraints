//
// Created by arseniy on 14.1.25.
//

#ifndef DEFAULTEXPORTERFACTORY_H
#define DEFAULTEXPORTERFACTORY_H
#include "AbstractExporter.h"
#include "components/IComponentFactory.h"


class DefaultExporterFactory : public IComponentFactory<AbstractExporter>
{
public:
    std::shared_ptr<AbstractExporter> createComponent(ComponentConfig &config, ReaderContext &context) override;
};



#endif //DEFAULTEXPORTERFACTORY_H
