//
// Created by arseniy on 11.1.25.
//

#ifndef RAPIDCOLLISIONHANDLERFACTORY_H
#define RAPIDCOLLISIONHANDLERFACTORY_H
#include "ICollisionHandler.h"
#include "components/IComponentFactory.h"
#include "core/reader/IReader.h"
#include "input/ComponentsParser.h"

class RapidCollisionHandlerFactory : public IComponentFactory<ICollisionHandler>
{
public:
    std::shared_ptr<ICollisionHandler> createComponent(const ComponentConfig &config, const ReaderContext &context) override;


};


#endif //RAPIDCOLLISIONHANDLERFACTORY_H
