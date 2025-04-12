//
// Created by arseniy on 12.4.25.
//

#ifndef FUELSTATE_H
#define FUELSTATE_H

class FuelState
{
public:
    FuelState(double main_thruster_fuel, double rotation_thrusters_fuel)
        : rotationThrustersFuel(rotation_thrusters_fuel),
          mainThrusterFuel(main_thruster_fuel) {}

    double getMainThrusterFuel() const { return mainThrusterFuel; }
    double getRotationThrustersFuel() const { return rotationThrustersFuel; }
private:
    double rotationThrustersFuel;
    double mainThrusterFuel;
};

#endif //FUELSTATE_H
