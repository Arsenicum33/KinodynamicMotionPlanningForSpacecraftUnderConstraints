// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef IPLANNER_H
#define IPLANNER_H
#include <components/IComponent.h>
#include <components/dynamicsSimulators/IDynamicsSimulator.h>
#include <dto/controlInputPlan/ControlInputPlan.h>

#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

template <typename StateType>
class IPlanner : public IComponent
{
public:
    IPlanner(double timeResolution) : timeResolution(timeResolution) {}
    virtual StateType executeControlInputPlan(const StateType& initialState, const ControlInputPlan& plan);

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    ComponentType getType() const override { return ComponentType::Planner; };

protected:
    std::shared_ptr<IDynamicsSimulator<StateType>> dynamicsSimulator;
    double timeResolution;
};

template<typename StateType>
StateType IPlanner<StateType>::executeControlInputPlan(const StateType &initialState,
    const ControlInputPlan& plan)
{
    StateType currentState = initialState;
    for (const auto& segment : plan.getSegments())
    {
        double timeLeft = segment.duration;
        while (timeLeft > 0)
        {
            double stepTime = std::min(timeLeft, timeResolution);
            currentState = dynamicsSimulator->integrate(currentState,  *(segment.controlInput.get()),stepTime);
            timeLeft -= stepTime;
        }

    }
    return currentState;
}

template<typename StateType>
void IPlanner<StateType>::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IComponent::resolveDependencies(config, manager);
    dynamicsSimulator = std::dynamic_pointer_cast<IDynamicsSimulator<StateType>>(
        manager->getComponent(ComponentType::DynamicsSimulator));
}

#endif //IPLANNER_H
