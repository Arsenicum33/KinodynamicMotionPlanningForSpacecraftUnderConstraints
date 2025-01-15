//
// Created by arseniy on 15.1.25.
//

#ifndef RAPIDDYNAMICCOLLISIONHANDLERFACTORY_H
#define RAPIDDYNAMICCOLLISIONHANDLERFACTORY_H
#include <components/collisionHandlers/ICollisionHandler.h>

#include "components/IComponentFactory.h"


class RapidDynamicCollisionHandlerFactory : public IComponentFactory<ICollisionHandler>
{
public:
    std::shared_ptr<ICollisionHandler> createComponent(ComponentConfig& config, ReaderContext& context) override;

};



#endif //RAPIDDYNAMICCOLLISIONHANDLERFACTORY_H
