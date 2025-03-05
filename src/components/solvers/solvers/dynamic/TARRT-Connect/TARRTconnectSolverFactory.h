//
// Created by arseniy on 19.1.25.
//

#ifndef TARRTCONNECTSOLVERFACTORY_H
#define TARRTCONNECTSOLVERFACTORY_H
#include "TARRTconnectSolver.h"
#include "components/IComponentFactory.h"


class TARRTconnectSolverFactory : IComponentFactory<TARRTconnectSolver>
{
public:
    std::unique_ptr<TARRTconnectSolver> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //TARRTCONNECTSOLVERFACTORY_H
