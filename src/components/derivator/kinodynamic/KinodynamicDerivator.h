//
// Created by arseniy on 30.4.25.
//

#ifndef KINODYNAMICDERIVATOR_H
#define KINODYNAMICDERIVATOR_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/derivator/IDerivator.h"


class KinodynamicDerivator : public IDerivator<State>
{
public:
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; }

    State derive(const State &currentState, const BurstControlInput &controlInput) override;
};



#endif //KINODYNAMICDERIVATOR_H
