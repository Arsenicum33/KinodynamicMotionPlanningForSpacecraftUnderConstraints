//
// Created by arseniy on 7.4.25.
//

#ifndef SIMPLECONTINUOUSPROPULSIONSYSTEM_H
#define SIMPLECONTINUOUSPROPULSIONSYSTEM_H
#include <dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h>

#include "components/propulsionSystem/IPropulsionSystem.h"


class SimpleContinuousPropulsionSystem : public IPropulsionSystem<ControlInput>
{
public:
    explicit SimpleContinuousPropulsionSystem(double inputDuration)
        : inputDuration(inputDuration) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv, Capability::AstrodynamicEnv}; }

    ComponentType getType() const override { return ComponentType::PropulsionSystem; }

private:
    AccelerationProfile<ControlInput> generateAccelerationProfile(const ControlInput &controlInput) override;
    double inputDuration;

};

#endif //SIMPLECONTINUOUSPROPULSIONSYSTEM_H
