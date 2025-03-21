//
// Created by arseniy on 21.3.25.
//

#ifndef DYNAMICSSIMULATOR_H
#define DYNAMICSSIMULATOR_H
#include "IDynamicsSimulator.h"
#include "dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"
#include "utils/PhysicsUtils.h"

class DynamicsSimulator : public IDynamicsSimulator<State, ControlInput>
{
public:
    explicit DynamicsSimulator(double timeStep)
        : timeStep(timeStep) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv }; }

    State computeNextState(const State &currentState, const ControlInput &controlInput) override;

protected:
    double timeStep;
};



#endif //DYNAMICSSIMULATOR_H
