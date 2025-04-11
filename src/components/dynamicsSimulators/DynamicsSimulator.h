//
// Created by arseniy on 21.3.25.
//

#ifndef DYNAMICSSIMULATOR_H
#define DYNAMICSSIMULATOR_H
#include "IDynamicsSimulator.h"
#include "dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"
#include "utils/PhysicsUtils.h"

class DynamicsSimulator : public IDynamicsSimulator
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv, Capability::AstrodynamicEnv }; }

    State computeNextState(const State &currentState, const TotalAcceleration &totalAcceleration, double timestep) override;
};



#endif //DYNAMICSSIMULATOR_H
