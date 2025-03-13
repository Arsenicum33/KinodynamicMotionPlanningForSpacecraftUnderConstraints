//
// Created by arseniy on 14.1.25.
//

#ifndef ISOLVER_H
#define ISOLVER_H
#include "components/IComponent.h"

template <typename ConfigType>
class ASolver : public IComponent
{
public:
    ;
    ASolver(ConfigType solverConfig, ConfigurationSpaceBoundaries boundaries) :
        config(solverConfig), boundaries(boundaries) {}

    ComponentType getType() const override { return ComponentType::Solver; };

protected:
    ConfigType config;
    ConfigurationSpaceBoundaries boundaries;
};



#endif //ISOLVER_H
