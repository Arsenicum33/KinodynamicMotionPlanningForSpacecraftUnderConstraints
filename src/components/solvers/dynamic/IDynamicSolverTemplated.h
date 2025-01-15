//
// Created by arseniy on 14.1.25.
//

#ifndef IDYNAMICSOLVERTERMPLATED_H
#define IDYNAMICSOLVERTERMPLATED_H
#include "IDynamicSolver.h"

template <typename ConfigType>
class IDynamicSolverTemplated : public IDynamicSolver
{
protected:
    IDynamicSolverTemplated(const ConfigType& config, const EnvSettings& envSettings) :
    config(config), boundaries(envSettings.boundaries) {}

    ConfigType config;
    ConfigurationSpaceBoundaries boundaries;
};

#endif //IDYNAMICSOLVERTERMPLATED_H
