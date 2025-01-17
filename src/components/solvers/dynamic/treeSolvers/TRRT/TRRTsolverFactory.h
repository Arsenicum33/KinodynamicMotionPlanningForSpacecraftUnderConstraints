//
// Created by arseniy on 15.1.25.
//

#ifndef TRRTSOLVERFACTORY_H
#define TRRTSOLVERFACTORY_H
#include "TRRTsolver.h"
#include "components/IComponentFactory.h"


class TRRTsolverFactory : public IComponentFactory<TRRTsolver>
{
public:
    std::shared_ptr<TRRTsolver> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //TRRTSOLVERFACTORY_H
