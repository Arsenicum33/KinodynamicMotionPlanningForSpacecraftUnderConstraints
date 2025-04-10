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
    explicit SimpleContinuousPropulsionSystem(double profileDuration)
        : profileDuration(profileDuration) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv, Capability::AstrodynamicEnv}; }

    ComponentType getType() const override { return ComponentType::PropulsionSystem; }

private:
    ControlInputPlan<ControlInput> generateAccelerationProfile(const ControlInput &controlInput) override;
    double profileDuration;

};

#endif //SIMPLECONTINUOUSPROPULSIONSYSTEM_H
