//
// Created by arseniy on 8.5.25.
//

#include "SpacecraftModel.h"

std::unique_ptr<IComponent> SpacecraftModel::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double dryMass = std::any_cast<double>(configMap.at("dryMass"));
    double mainThrusterInitialFuel = std::any_cast<double>(configMap.at("mainThrusterInitialFuel"));
    double rotationalThrusterInitialFuel = std::any_cast<double>(configMap.at("rotationalThrusterInitialFuel"));
    double mainThrusterFuelToMassRatio = std::any_cast<double>(configMap.at("mainThrusterFuelToMassRatio"));
    double rotationThrustersFuelToMassRatio = std::any_cast<double>(configMap.at("rotationThrustersFuelToMassRatio"));

    return std::make_unique<SpacecraftModel>(dryMass, FuelState(mainThrusterInitialFuel, rotationalThrusterInitialFuel),
        mainThrusterFuelToMassRatio, rotationThrustersFuelToMassRatio);
}

double SpacecraftModel::getTotalMass(const SpaceshipState &state) const
{
    return dryMass + initialFuel.getMainThrusterFuel() * mainThrusterFuelToMassRatio +
           initialFuel.getRotationThrustersFuel() * rotationThrustersFuelToMassRatio;
}


//Tensor for a sphere with spacecraft's mass and given density
Eigen::Matrix3d SpacecraftModel::getInertiaTensor(const SpaceshipState &state) const
{
    double mass = getTotalMass(state);
    double constant = (3.0 / (4.0 * PI * SPACESHIP_DENSITY));
    double moment = (2.0/5.0) * std::pow(constant, 2.0 / 3.0) * std::pow(mass, 5.0 / 3.0);
    Eigen::Matrix3d inertiaTensor = Eigen::Matrix3d::Zero();
    inertiaTensor(0, 0) = moment;
    inertiaTensor(1, 1) = moment;
    inertiaTensor(2, 2) = moment;
    return inertiaTensor;
}
