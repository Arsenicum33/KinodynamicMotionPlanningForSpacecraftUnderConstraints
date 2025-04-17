//
// Created by arseniy on 16.4.25.
//

#ifndef FUELSYSTEM_H
#define FUELSYSTEM_H
#include "IFuelSystem.h"

class FuelSystem : public IFuelSystem
{
public:
    FuelSystem(double thrustToFuelFlowRation, double torqueToFuelFlowRatio) :
        thrustToFuelFlowRatio(thrustToFuelFlowRation), torqueToFuelFlowRatio(torqueToFuelFlowRatio) {}
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; };

    FuelState getNextFuelState(const FuelState &currentFuelState, const TotalForce &totalForce, double timestep) override;

private:
    double thrustToFuelFlowRatio;
    double torqueToFuelFlowRatio;
};


#endif //FUELSYSTEM_H
