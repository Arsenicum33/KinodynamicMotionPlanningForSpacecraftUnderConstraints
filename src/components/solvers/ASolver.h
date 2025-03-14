//
// Created by arseniy on 14.1.25.
//

#ifndef ISOLVER_H
#define ISOLVER_H
#include "components/IComponent.h"


class ASolver : public IComponent
{
public:
    ComponentType getType() const override { return ComponentType::Solver; };
};



#endif //ISOLVER_H
