//
// Created by arseniy on 10.3.25.
//

#ifndef MT_TARRTSOLVERFACTORY_H
#define MT_TARRTSOLVERFACTORY_H
#include <memory>

#include "MT_TARRTsolver.h"
#include "components/IComponentFactory.h"
#include "components/solvers/solvers/dynamic/TARRT/TARRTsolver.h"
#include "core/reader/IReader.h"
#include "input/ComponentsParser.h"


class MT_TARRTsolverFactory : public IComponentFactory<MT_TARRTsolver>
{
public:
    std::unique_ptr<MT_TARRTsolver> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //MT_TARRTSOLVERFACTORY_H
