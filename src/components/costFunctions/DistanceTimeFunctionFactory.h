//
// Created by arseniy on 15.1.25.
//

#ifndef DISTANCETIMEFUNCTIONFACTORY_H
#define DISTANCETIMEFUNCTIONFACTORY_H
#include "DistanceTimeFunction.h"
#include "components/IComponent.h"
#include "components/IComponentFactory.h"


class DistanceTimeFunctionFactory : public IComponentFactory<DistanceTimeFunction>
{
public:
    std::shared_ptr<DistanceTimeFunction> createComponent(ComponentConfig &config, ReaderContext &context) override;
};



#endif //DISTANCETIMEFUNCTIONFACTORY_H
