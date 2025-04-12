//
// Created by arseniy on 7.4.25.
//

#ifndef STATE_BURSTCONTROLINPUT_STATEPROPAGATOR_H
#define STATE_BURSTCONTROLINPUT_STATEPROPAGATOR_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "StatePropagator.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class State_BurstControlInput_StatePropagator : public StatePropagator<State, BurstControlInput>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv}; }
};

inline std::unique_ptr<IComponent> State_BurstControlInput_StatePropagator::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<State_BurstControlInput_StatePropagator>();
}
#endif //STATE_BURSTCONTROLINPUT_STATEPROPAGATOR_H
