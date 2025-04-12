//
// Created by arseniy on 9.4.25.
//

#ifndef SPACESHIPMODEL_H
#define SPACESHIPMODEL_H
#include <any>
#include <string>
#include <unordered_map>

#include "dto/fuelState/FuelState.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class SpaceshipModel
{
public:
    SpaceshipModel(std::unordered_map<std::string, std::any> modelRaw) :
    dryMass(std::any_cast<double>(modelRaw["dry_mass"])),
     initialFuel(std::any_cast<double>(modelRaw["main_thruster_fuel"]),
         std::any_cast<double>(modelRaw["rotation_thrusters_fuel"])),
     mainThrusterFuelToMassRatio(std::any_cast<double>(modelRaw["main_thruster_fuel_to_mass_ratio"])),
    rotationThrustersFuelToMassRatio(std::any_cast<double>(modelRaw["rotation_thrusters_fuel_to_mass_ratio"])) {};

    double getDryMass() const { return dryMass; }
    const FuelState& getInitialFuel() const { return initialFuel; }
    double getMainThrusterFuelToMassRatio() const { return mainThrusterFuelToMassRatio; }
    double getRotationThrustersFuelToMassRatio() const { return rotationThrustersFuelToMassRatio; }

    double getTotalMass(const SpaceshipState& state) const
    {
        return dryMass + initialFuel.getMainThrusterFuel() * mainThrusterFuelToMassRatio +
            initialFuel.getRotationThrustersFuel() * rotationThrustersFuelToMassRatio;
    }
    Eigen::Matrix3d getInertiaTensor(const SpaceshipState& state) const; //TODO make it config dependent
private:
    double dryMass;
    FuelState initialFuel;
    double mainThrusterFuelToMassRatio;
    double rotationThrustersFuelToMassRatio;
};



#endif //SPACESHIPMODEL_H
