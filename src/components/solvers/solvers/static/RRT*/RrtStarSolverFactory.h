//
// Created by arseniy on 14.1.25.
//

#ifndef RRTSTARSOLVERFACTORY_H
#define RRTSTARSOLVERFACTORY_H

#include "RrtStarSolver.h"
#include "components/IComponentFactory.h"


class RrtStarSolverFactory : public IComponentFactory<RrtStarSolver>
{
public:
    std::unique_ptr<RrtStarSolver> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //RRTSTARSOLVERFACTORY_H
