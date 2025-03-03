//
// Created by arseniy on 14.1.25.
//

#ifndef RRTSTARSOLVERFACTORY_H
#define RRTSTARSOLVERFACTORY_H

#include "components/IComponentFactory.h"
#include "components/solvers/IStaticSolver.h"


class RrtStarSolverFactory : public IComponentFactory<IStaticSolver>
{
public:
    std::unique_ptr<IStaticSolver> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //RRTSTARSOLVERFACTORY_H
