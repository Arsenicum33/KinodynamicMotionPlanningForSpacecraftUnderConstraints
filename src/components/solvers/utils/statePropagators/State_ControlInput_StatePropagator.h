//
// Created by arseniy on 7.4.25.
//

#ifndef STATE_CONTROLINPUT_STATEPROPAGATOR_H
#define STATE_CONTROLINPUT_STATEPROPAGATOR_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "StatePropagator.h"

class State_ControlInput_StatePropagator : public StatePropagator<State, ControlInput>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv}; }
};

inline std::unique_ptr<IComponent> State_ControlInput_StatePropagator::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<State_ControlInput_StatePropagator>();
}
#endif //STATE_CONTROLINPUT_STATEPROPAGATOR_H
