//
// Created by arseniy on 21.3.25.
//

#ifndef IDYNAMICSSIMULATOR_H
#define IDYNAMICSSIMULATOR_H
#include <dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/IComponent.h"
#include "dto/totalAcceleration/TotalAcceleration.h"

class IDynamicsSimulator : public IComponent
{
public:
    virtual State computeNextState(const State& currentState, const TotalAcceleration& totalAcceleration, double timestep) = 0;

    ComponentType getType() const override { return ComponentType::DynamicsSimulator; }
};

#endif //IDYNAMICSSIMULATOR_H
