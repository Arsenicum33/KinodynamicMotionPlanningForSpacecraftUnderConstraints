// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef FUELSYSTEM_H
#define FUELSYSTEM_H
#include "IFuelSystem.h"

class FuelSystem : public IFuelSystem
{
public:
    FuelSystem(double thrustToFuelFlowRation, double torqueToFuelFlowRatio) :
      IFuelSystem(thrustToFuelFlowRation, torqueToFuelFlowRatio) {}
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; };

    FuelState getNextFuelState(const FuelState &currentFuelState, const TotalForce &totalForce, double timestep) override;

    FuelState getNextFuelState(const FuelState &currentFuelState, double thrust, double torque, double timestep) override;

};


#endif //FUELSYSTEM_H
