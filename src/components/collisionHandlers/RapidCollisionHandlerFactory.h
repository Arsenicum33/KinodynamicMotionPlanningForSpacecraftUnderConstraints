//
// Created by arseniy on 11.1.25.
//

#ifndef RAPIDCOLLISIONHANDLERFACTORY_H
#define RAPIDCOLLISIONHANDLERFACTORY_H
#include "ICollisionHandler.h"
#include "components/IComponentFactory.h"

class RapidCollisionHandlerFactory : public IComponentFactory<ICollisionHandler>
{
public:
    ICollisionHandler* createComponent(std::unordered_map<std::string, std::any> data) override;
};


#endif //RAPIDCOLLISIONHANDLERFACTORY_H
