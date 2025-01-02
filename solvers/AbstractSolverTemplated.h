//
// Created by arseniy on 12.10.24.
//

#ifndef ABSTRACTSOLVERTEMPLATED_H
#define ABSTRACTSOLVERTEMPLATED_H
#include <memory>
#include <RAPID.H>

#include <vector>
#include "../poses/static/Pose.h"
#include "../ConfigurationSpaceBoundaries.h"
#include "configs/AbstractSolverConfig.h"
#include "../EnvSettings.h"
template <typename ConfigType>
class AbstractSolverTemplated : public AbstractSolver
{
public:
    AbstractSolverTemplated(const ConfigType& config, const EnvSettings& envSettings) :
        config(config), boundaries(envSettings.boundaries) {}

    ConfigType config;
    ConfigurationSpaceBoundaries boundaries;
};



#endif //ABSTRACTSOLVERTEMPLATED_H
