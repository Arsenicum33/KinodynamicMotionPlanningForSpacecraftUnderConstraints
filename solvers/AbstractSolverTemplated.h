//
// Created by arseniy on 12.10.24.
//

#ifndef ABSTRACTSOLVERTEMPLATED_H
#define ABSTRACTSOLVERTEMPLATED_H
#include <memory>
#include <RAPID.H>

#include <vector>
#include "../poses/Pose.h"
#include "../ConfigurationSpaceBoundaries.h"
#include "configs/AbstractSolverConfig.h"

template <typename ConfigType>
class AbstractSolverTemplated : public AbstractSolver
{
public:
    AbstractSolverTemplated(const ConfigType& config) : config(config) {}

    ConfigType config;
};



#endif //ABSTRACTSOLVERTEMPLATED_H
