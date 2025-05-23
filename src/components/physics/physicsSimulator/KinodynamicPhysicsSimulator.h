// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef KINODYNAMICPHYSICSSIMULATOR_H
#define KINODYNAMICPHYSICSSIMULATOR_H
#include "PhysicsSimulator.h"

class KinodynamicPhysicsSimulator : public PhysicsSimulator<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; }

    TotalAcceleration computeAcceleration(const State &currentState, const BurstControlInput &controlInput) override;
};

inline std::unique_ptr<IComponent> KinodynamicPhysicsSimulator::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<KinodynamicPhysicsSimulator>();
}

inline TotalAcceleration KinodynamicPhysicsSimulator::computeAcceleration(const State &currentState,
    const BurstControlInput &controlInput)
{
    TotalForce internalForce = internalForcesComputer->computeTotalForce(currentState, controlInput);
    TotalAcceleration acceleration = forceToAccelerationConverter->convert(internalForce, currentState);
    return acceleration;
}


#endif //KINODYNAMICPHYSICSSIMULATOR_H
