// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IFUELSYSTEM_H
#define IFUELSYSTEM_H
#include <components/IComponent.h>

#include "components/physics/totalForce/TotalForce.h"
#include "dto/fuelState/FuelState.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class IFuelSystem : public IComponent
{
public:
    IFuelSystem(double thrustToFuelFlowRatio, double torqueToFuelFlowRatio)
        : thrustToFuelFlowRatio(thrustToFuelFlowRatio),
          torqueToFuelFlowRatio(torqueToFuelFlowRatio)
    {}

    virtual FuelState getNextFuelState(const FuelState& currentFuelState, const TotalForce& totalForce, double timestep) = 0;
    virtual FuelState getNextFuelState(const FuelState &currentFuelState, double thrust, double torque, double timestep) = 0;

    double getThrustToFuelFlowRation() { return thrustToFuelFlowRatio; }


    double getTorqueToFuelFlowRatio() { return torqueToFuelFlowRatio; }

    ComponentType getType() const override { return ComponentType::FuelSystem;};

protected:
    double thrustToFuelFlowRatio;
    double torqueToFuelFlowRatio;
};
#endif //IFUELSYSTEM_H
