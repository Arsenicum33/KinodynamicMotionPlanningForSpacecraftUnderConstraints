//
// Created by arseniy on 9.4.25.
//

#ifndef SPACESHIPMODEL_H
#define SPACESHIPMODEL_H
#include <any>
#include <string>
#include <unordered_map>

#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class SpaceshipModel
{
public:
    SpaceshipModel(std::unordered_map<std::string, std::any> modelRaw) :
    dryMass(std::any_cast<double>(modelRaw["dry_mass"])),
     initialFuel(std::any_cast<double>(modelRaw["initial_fuel"])),
     fuelToMassRatio(std::any_cast<double>(modelRaw["fuel_to_mass_ratio"])){};

    double getDryMass() const { return dryMass; }
    double getInitialFuel() const { return initialFuel; }
    double getFuelToMassRatio() const { return fuelToMassRatio; }

    double getTotalMass(const SpaceshipState& state) { return state.getFuel() * fuelToMassRatio + dryMass; }
    Eigen::Matrix3d getInertiaTensor(const SpaceshipState& state);
private:
    double dryMass;
    double initialFuel;
    double fuelToMassRatio;
};



#endif //SPACESHIPMODEL_H
