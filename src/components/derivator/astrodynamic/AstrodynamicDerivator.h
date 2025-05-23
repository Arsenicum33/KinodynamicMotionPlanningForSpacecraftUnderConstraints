// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ASTRODYNAMICDERIVATOR_H
#define ASTRODYNAMICDERIVATOR_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/derivator/IDerivator.h"
#include "components/derivator/kinodynamic/KinodynamicDerivator.h"
#include "components/fuelSystem/IFuelSystem.h"
#include "components/physics/physicsSimulator/IPhysicsSimulator.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicDerivator : public IDerivator<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<AstrodynamicDerivator>();
    }
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv}; }

    SpaceshipState derive(const SpaceshipState &currentState, const BurstControlInput &controlInput) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    std::shared_ptr<IPhysicsSimulator<SpaceshipState>> physicsSimulator;
    std::shared_ptr<IFuelSystem> fuelSystem;
};



#endif //ASTRODYNAMICDERIVATOR_H
