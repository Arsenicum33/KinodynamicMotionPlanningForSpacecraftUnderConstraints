//
// Created by arseniy on 17.1.25.
//

#ifndef DEFAULTDYNAMICEXPORTERFACTORY_H
#define DEFAULTDYNAMICEXPORTERFACTORY_H
#include "AbstractExporter.h"
#include "components/IComponentFactory.h"


class DefaultDynamicExporterFactory : public IComponentFactory<AbstractExporter<Keyframe>>
{
public:
    std::shared_ptr<AbstractExporter<Keyframe>> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //DEFAULTDYNAMICEXPORTERFACTORY_H
