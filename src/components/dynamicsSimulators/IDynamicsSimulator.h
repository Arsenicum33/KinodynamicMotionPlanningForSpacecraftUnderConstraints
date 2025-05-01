//
// Created by arseniy on 21.3.25.
//

#ifndef IDYNAMICSSIMULATOR_H
#define IDYNAMICSSIMULATOR_H
#include <dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/IComponent.h"
#include "components/derivator/IDerivator.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"
#include "dto/totalAcceleration/TotalAcceleration.h"

template <typename StateType>
class IDynamicsSimulator : public IComponent
{
public:
    virtual StateType integrate(const StateType& currentState,const BurstControlInput& controlInput, double timestep) = 0;

    ComponentType getType() const override { return ComponentType::DynamicsSimulator; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    std::shared_ptr<IDerivator<StateType>> derivator;
};

template<typename StateType>
void IDynamicsSimulator<StateType>::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IComponent::resolveDependencies(config, manager);
    derivator = std::dynamic_pointer_cast<IDerivator<StateType>>(
        manager->getComponent(ComponentType::Derivator));
}

#endif //IDYNAMICSSIMULATOR_H
