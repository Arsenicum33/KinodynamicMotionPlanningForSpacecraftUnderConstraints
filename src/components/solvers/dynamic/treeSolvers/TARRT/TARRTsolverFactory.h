//
// Created by arseniy on 15.1.25.
//

#ifndef TRRTSOLVERFACTORY_H
#define TRRTSOLVERFACTORY_H
#include "TARRTsolver.h"
#include "components/IComponentFactory.h"


class TARRTsolverFactory : public IComponentFactory<TARRTsolver>
{
public:
    std::unique_ptr<TARRTsolver> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //TRRTSOLVERFACTORY_H
