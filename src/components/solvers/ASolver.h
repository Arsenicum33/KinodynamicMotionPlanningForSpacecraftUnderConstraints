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
    std::string getName() const override { return "Solver"; };
    ASolver(ConfigType solverConfig, ConfigurationSpaceBoundaries boundaries) :
        config(solverConfig), boundaries(boundaries) {}
protected:
    ConfigType config;
    ConfigurationSpaceBoundaries boundaries;
};



#endif //ISOLVER_H
