// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef KINODYNAMICDERIVATOR_H
#define KINODYNAMICDERIVATOR_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/derivator/IDerivator.h"
#include "components/physics/physicsSimulator/IPhysicsSimulator.h"


class KinodynamicDerivator : public IDerivator<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<KinodynamicDerivator>();
    }

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; }

    State derive(const State &currentState, const BurstControlInput &controlInput) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    std::shared_ptr<IPhysicsSimulator<State>> physicsSimulator;
};



#endif //KINODYNAMICDERIVATOR_H
