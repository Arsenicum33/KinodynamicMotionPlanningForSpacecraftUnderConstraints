//
// Created by arseniy on 14.1.25.
//

#ifndef ISOLVER_H
#define ISOLVER_H
#include "components/IComponent.h"


class ISolver : public IComponent
{
    std::string getName() const override { return "Solver"; };
};



#endif //ISOLVER_H
