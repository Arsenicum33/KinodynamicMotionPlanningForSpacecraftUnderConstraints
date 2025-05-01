//
// Created by arseniy on 9.4.25.
//

#ifndef SPACESHIPSTATE_H
#define SPACESHIPSTATE_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "dto/fuelState/FuelState.h"


class SpaceshipState : public State
{
public:
    SpaceshipState(State state, FuelState fuel) : State(state), fuel(fuel) {}
    const FuelState& getFuel() const { return fuel; }
    void setFuel(FuelState fuel) { this->fuel = fuel; }

    SpaceshipState operator+(const SpaceshipState &other) const; //only for operations with derivative

    SpaceshipState operator*(double factor) const; //only for operations with derivative
private:
    FuelState fuel;
};



#endif //SPACESHIPSTATE_H
