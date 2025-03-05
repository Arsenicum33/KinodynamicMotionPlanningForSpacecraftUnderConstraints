//
// Created by arseniy on 14.1.25.
//

#ifndef RRTSOLVERFACTORY_H
#define RRTSOLVERFACTORY_H
#include "RRTsolver.h"
#include "components/IComponentFactory.h"


class RRTsolverFactory : public IComponentFactory<RRTsolver>
{
public:
    std::unique_ptr<RRTsolver> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //RRTSOLVERFACTORY_H
