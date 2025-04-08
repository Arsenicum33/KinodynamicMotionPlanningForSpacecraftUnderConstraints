//
// Created by arseniy on 21.3.25.
//

#ifndef DYNAMICSSIMULATOR_H
#define DYNAMICSSIMULATOR_H
#include "IDynamicsSimulator.h"
#include "dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"
#include "utils/PhysicsUtils.h"

class BurstDynamicsSimulatorAdapter;

class DynamicsSimulator : public IDynamicsSimulator<State, ControlInput>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv }; }
    friend BurstDynamicsSimulatorAdapter;
protected:
    State computeSegmentTransition(const State &currentState,
        const AccelerationProfile<ControlInput>::Segment& segment) override;
};



#endif //DYNAMICSSIMULATOR_H
