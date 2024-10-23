//
// Created by arseniy on 23.10.24.
//

#ifndef SOLVERFACTORY_H
#define SOLVERFACTORY_H
#include <jsoncpp/json/json.h>

#include "AbstractSolverConfig.h"
#include <fstream>
#include "../AbstractSolver.h"

#include "treeSolverConfigs/RRT*/RrtStarSolverConfig.h"
#include "treeSolverConfigs/RRT/RRTsolverConfig.h"
#include "cassert"
class SolverFactory
{
public:
    static std::unique_ptr<AbstractSolver> createSolverFromConfig(const std::string& filepath);

};



#endif //SOLVERFACTORY_H
