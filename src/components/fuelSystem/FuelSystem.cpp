// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "FuelSystem.h"

std::unique_ptr<IComponent> FuelSystem::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double thrustToFuelFlowRatio = std::any_cast<double>(configMap.at("thrustToFuelFlowRatio"));
    double torqueToFuelFlowRatio = std::any_cast<double>(configMap.at("torqueToFuelFlowRatio"));

    return std::make_unique<FuelSystem>(thrustToFuelFlowRatio, torqueToFuelFlowRatio);
}

FuelState FuelSystem::getNextFuelState(const FuelState &currentFuelState, const TotalForce &totalForce, double timestep)
{
    using namespace PhysicsUtils;
    double mainThrusterFuel = currentFuelState.getMainThrusterFuel() - norm(totalForce.getForce()) *
        thrustToFuelFlowRatio * timestep;
    double rotationThrustersFuel = currentFuelState.getRotationThrustersFuel() - norm(totalForce.getTorque()) *
        torqueToFuelFlowRatio * timestep;
    return FuelState(mainThrusterFuel, rotationThrustersFuel);
}

FuelState FuelSystem::getNextFuelState(const FuelState &currentFuelState, double thrust, double torque, double timestep)
{
    using namespace PhysicsUtils;
    double mainThrusterFuel = currentFuelState.getMainThrusterFuel() - thrust *
        thrustToFuelFlowRatio * timestep;
    double rotationThrustersFuel = currentFuelState.getRotationThrustersFuel() - torque *
        torqueToFuelFlowRatio * timestep;
    return FuelState(mainThrusterFuel, rotationThrustersFuel);
}
